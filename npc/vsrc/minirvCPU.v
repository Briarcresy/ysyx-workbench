module minirvCPU #(
    parameter DATA_WIDTH = 32
) (
    input                   clk,
    input                   rst,
    input  [DATA_WIDTH-1:0] inst,
    output [DATA_WIDTH-1:0] pc,
    output                  debug_wb_we,
    output [           3:0] debug_wb_rd,
    output [DATA_WIDTH-1:0] debug_wb_data
);
    //minirv规范：
    // PC初值为0
    // GPR数量与RV32E中定义的GPR数量一致
    // 支持如下8条指令: add, addi, lui, lw, lbu, sw, sb, jalr
    // 其他的ISA细节与RV32I相同

    wire [3:0] rs1, rs2, rd;
    wire [DATA_WIDTH-1:0] R_rs1, R_rs2, R_rd;
    wire [DATA_WIDTH-1:0] imm;
    wire [DATA_WIDTH-1:0] src1, src2;
    wire [DATA_WIDTH-1:0] result;
    wire [3:0] alu_op;
    wire alu_src2_imm;
    wire decoded_reg_we;
    wire reg_we;

    assign rs1 = inst[18:15];
    assign rs2 = inst[23:20];
    assign rd = inst[10:7];
    assign reg_we = decoded_reg_we && !rst && (rd != 0);

    PC #(
        .DATA_WIDTH(DATA_WIDTH)
    ) pc_reg (
        .clk(clk),
        .rst(rst),
        .pc (pc)
    );

    Controller controller (
        .opcode      (inst[6:0]),
        .funct3      (inst[14:12]),
        .reg_we      (decoded_reg_we),
        .alu_op      (alu_op),
        .alu_src2_imm(alu_src2_imm)
    );

    RegFile #(
        .ADDR_WIDTH(4),
        .DATA_WIDTH(DATA_WIDTH)
    ) reg_file (
        .clk  (clk),
        .we   (reg_we),
        .rs1  (rs1),
        .rs2  (rs2),
        .rd   (rd),
        .R_rd (R_rd),
        .R_rs1(R_rs1),
        .R_rs2(R_rs2)
    );

    ALU #(
        .DATA_WIDTH(DATA_WIDTH)
    ) alu (
        .src1  (src1),
        .src2  (src2),
        .op    (alu_op),
        .result(result)
    );

    ImmGen #(
        .DATA_WIDTH(DATA_WIDTH)
    ) imm_gen (
        .inst(inst),
        .imm (imm)
    );

    assign src1 = R_rs1;
    assign src2 = alu_src2_imm ? imm : R_rs2;
    assign R_rd = result;

    assign debug_wb_we = reg_we;
    assign debug_wb_rd = rd;
    assign debug_wb_data = result;

endmodule
