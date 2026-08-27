module Controller (
    input  [6:0] opcode,
    input  [2:0] funct3,
    output       reg_we,
    output [3:0] alu_op,
    output       alu_src1_pc,
    output       alu_src2_imm,
    output       jump,
    output       trap,
    output       mem_valid,
    output       mem_wen,
    output [1:0] R_rd_sel
);

    `define R_TYPE 7'b011_0011
    `define I_TYPE 7'b001_0011
    `define IL_TYPE 7'b000_0011 // I load
    `define IJ_TYPE 7'b110_0111 // I jalr
    `define S_TYPE 7'b010_0011
    `define B_TYPE 7'b110_0011
    `define U_TYPE 7'b011_0111 // U lui
    `define UA_TYPE 7'b001_0111 // U auipc
    `define J_TYPE 7'b110_1111

    wire rtype, itype, jalr, lui, load, store;
    wire op_add;

    assign rtype = (opcode == `R_TYPE);
    assign itype = (opcode == `I_TYPE);
    assign jalr = (opcode == `IJ_TYPE);
    assign lui = (opcode == `U_TYPE);
    assign load = (opcode == `IL_TYPE);
    assign store = (opcode == `S_TYPE);

    assign op_add = rtype || (itype && funct3 == 3'b000) || jalr || load || store;

    assign reg_we = rtype || itype || jalr || lui || load;
    assign alu_op = {3'b000, op_add};
    assign alu_src1_pc = 0;
    assign alu_src2_imm = itype || jalr || load || store;
    assign jump = jalr;
    assign trap = (opcode == 7'b111_0011);
    assign mem_valid = load || store;
    assign mem_wen = store;
    assign R_rd_sel = ({2{rtype | itype}} & 2'b00) | ({2{jalr}} & 2'b01) | ({2{lui}} & 2'b10) | ({2{load}} & 2'b11);

endmodule
