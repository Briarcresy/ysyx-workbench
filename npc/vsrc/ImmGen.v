module ImmGen #(
    DATA_WIDTH = 32
) (
    input  [DATA_WIDTH-1:0] inst,
    output [DATA_WIDTH-1:0] imm
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

    wire [6:0] opcode;
    wire R_type, I_type, S_type, B_type, U_type, J_type;

    assign opcode = inst[6:0];

    assign R_type = (opcode == `R_TYPE);
    assign I_type = (opcode == `I_TYPE || opcode == `IL_TYPE || opcode == `IJ_TYPE);
    assign S_type = (opcode == `S_TYPE);
    assign B_type = (opcode == `B_TYPE);
    assign U_type = (opcode == `U_TYPE || opcode == `UA_TYPE);
    assign J_type = (opcode == `J_TYPE);

    assign imm =
        ({32{R_type}} & 32'b0) |
        ({32{I_type}} & {{20{inst[31]}}, inst[31:20]}) |
        ({32{S_type}} & {{20{inst[31]}}, inst[31:25], inst[11:7]}) |
        ({32{B_type}} & {
            {19{inst[31]}}, inst[31], inst[7], inst[30:25], inst[11:8], 1'b0
        }) |
        ({32{U_type}} & {inst[31:12], 12'b0}) |
        ({32{J_type}} & {
            {11{inst[31]}}, inst[31], inst[19:12], inst[20], inst[30:21], 1'b0
        });

endmodule
