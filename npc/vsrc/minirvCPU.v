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

    wire [DATA_WIDTH-1:0] npc;
    wire [3:0] rs1, rs2, rd;
    wire [DATA_WIDTH-1:0] R_rs1, R_rs2, R_rd;
    wire [DATA_WIDTH-1:0] imm;
    wire [DATA_WIDTH-1:0] src1, src2;
    wire [DATA_WIDTH-1:0] result;
    wire [3:0] alu_op;
    wire alu_src1_pc, alu_src2_imm, reg_we, jump, trap;
    wire [DATA_WIDTH-1:0] pc_plus_4;

    assign rs1 = inst[18:15];
    assign rs2 = inst[23:20];
    assign rd = inst[10:7];

    assign pc_plus_4 = pc + 4;

    assign npc = jump ? {result & 32'hffff_fffe} : pc_plus_4;

    import "DPI-C" function void npc_trap();

    always @(posedge clk) begin
        if (!rst && trap) begin
            npc_trap();
        end
    end

    PC #(
        .DATA_WIDTH(DATA_WIDTH)
    ) pc_reg (
        .clk(clk),
        .rst(rst),
        .npc(npc),
        .pc (pc)
    );

    Controller controller (
        .opcode      (inst[6:0]),
        .funct3      (inst[14:12]),
        .reg_we      (reg_we),
        .alu_op      (alu_op),
        .alu_src1_pc (alu_src1_pc),
        .alu_src2_imm(alu_src2_imm),
        .jump        (jump),
        .trap        (trap)
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

    assign src1 = alu_src1_pc ? pc : R_rs1;
    assign src2 = alu_src2_imm ? imm : R_rs2;
    assign R_rd = jump ? pc_plus_4 : result;

    assign debug_wb_we = reg_we;
    assign debug_wb_rd = rd;
    assign debug_wb_data = R_rd;

endmodule
