module RegFile #(
    ADDR_WIDTH = 4,
    DATA_WIDTH = 32
) (
    input                   clk,
    input                   we,
    input  [ADDR_WIDTH-1:0] rs1,
    rs2,
    rd,
    input  [DATA_WIDTH-1:0] R_rd,
    output [DATA_WIDTH-1:0] R_rs1,
    R_rs2
);

    reg [DATA_WIDTH-1:0] R[0:2**ADDR_WIDTH-1];

    assign R_rs1 = (rs1 == 0) ? 0 : R[rs1];
    assign R_rs2 = (rs2 == 0) ? 0 : R[rs2];

    always @(posedge clk) begin
        if (we) begin
            R[rd] <= R_rd;
        end
    end

endmodule
