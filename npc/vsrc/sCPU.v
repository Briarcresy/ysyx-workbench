module sCPU (
    input clk,
    input rst,
    output reg [6:0] seg_out_0,
    output reg [6:0] seg_out_1
);

    wire [3:0] addr;
    wire [7:0] instr;
    wire [7:0] alu_res;
    wire jp;
    wire reg_we;
    wire reg_wr_sel;
    wire reg_rd1_sel;
    wire alu_op;
    wire out;
    wire [7:0] reg_rdata1;
    wire [7:0] reg_rdata2;
    wire [6:0] seg_in_0;
    wire [6:0] seg_in_1;
    wire [7:0] imm;

    assign imm = {4'b0000, instr[3:0]};

    PC pc (
        .clk(clk),
        .rst(rst),
        .jp_addr(instr[5:2]),
        .jp(jp),
        .addr(addr)
    );

    InstrMem instr_mem (
        .addr (addr),
        .instr(instr)
    );

    Controller controller (
        .opcode(instr[7:6]),
        .alu_res(alu_res),
        .jp(jp),
        .reg_we(reg_we),
        .reg_wr_sel(reg_wr_sel),
        .reg_rd1_sel(reg_rd1_sel),
        .alu_op(alu_op),
        .out(out)
    );

    RegFile reg_file (
        .clk(clk),
        .rst(rst),
        .rdata1(reg_rdata1),
        .rdata2(reg_rdata2),
        .raddr1(reg_rd1_sel ? 2'b00 : instr[3:2]),
        .raddr2(instr[1:0]),
        .waddr(instr[5:4]),
        .wdata(reg_wr_sel ? imm : alu_res),
        .we(reg_we)
    );

    ALU alu (
        .op (alu_op),
        .A  (reg_rdata1),
        .B  (reg_rdata2),
        .res(alu_res)
    );

    Seg7 seg7_0 (
        .dgt(reg_rdata2[3:0]),
        .seg(seg_in_0)
    );

    Seg7 seg7_1 (
        .dgt(reg_rdata2[7:4]),
        .seg(seg_in_1)
    );

    always @(posedge clk) begin
        if (rst) begin
            seg_out_0 <= 7'b1111111;
            seg_out_1 <= 7'b1111111;
        end else if (out) begin
            seg_out_0 <= seg_in_0;
            seg_out_1 <= seg_in_1;
        end
    end

endmodule
