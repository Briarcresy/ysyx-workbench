module Controller (
    input [1:0] opcode,
    input [7:0] alu_res,
    output jp,
    output reg_we,
    output reg_wr_sel,
    output reg_rd1_sel,
    output alu_op,
    output out
);

    assign jp = (opcode == 2'b11 && alu_res == 8'b00000001);
    assign reg_we = ~opcode[0];
    assign reg_wr_sel = opcode[1];
    assign reg_rd1_sel = opcode[1];
    assign alu_op = opcode[1];
    assign out = (opcode == 2'b01);

endmodule
