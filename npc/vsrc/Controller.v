module Controller (
    input  [6:0] opcode,
    input  [2:0] funct3,
    output       reg_we,
    output [3:0] alu_op,
    output       alu_src1_pc,
    output       alu_src2_imm,
    output       jump,
    output       trap
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

    wire itype, jalr;
    wire op_add;

    assign itype = (opcode == `I_TYPE);
    assign jalr = (opcode == `IJ_TYPE);

    assign op_add = (itype && funct3 == 3'b000) || jalr;

    assign reg_we = itype || jalr;
    assign alu_op = {3'b000, op_add};
    assign alu_src1_pc = 0;
    assign alu_src2_imm = itype || jalr;
    assign jump = jalr;
    assign trap = (opcode == 7'b111_0011);

endmodule
