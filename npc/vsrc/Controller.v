module Controller (
    input  [6:0] opcode,
    input  [2:0] funct3,
    output       reg_we,
    output [3:0] alu_op,
    output       alu_src2_imm
);

    `define R_TYPE 7'b011_0011
    `define I_TYPE 7'b001_0011
    `define IL_TYPE 7'b000_0011 // I lw
    `define IJ_TYPE 7'b110_0111 // I jalr
    `define S_TYPE 7'b010_0011
    `define B_TYPE 7'b110_0011
    `define U_TYPE 7'b011_0111 // U lui
    `define UA_TYPE 7'b001_0111 // U auipc
    `define J_TYPE 7'b110_1111

    wire addi = (opcode == `I_TYPE) && (funct3 == 3'b000);

    assign reg_we = addi;
    assign alu_op = addi ? 4'b0001 : 4'b0000;
    assign alu_src2_imm = addi;

endmodule
