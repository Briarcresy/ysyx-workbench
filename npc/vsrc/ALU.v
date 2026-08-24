module ALU #(
    DATA_WIDTH = 32
) (
    input      [DATA_WIDTH-1:0] src1,
    input      [DATA_WIDTH-1:0] src2,
    input      [           3:0] op,
    output reg [DATA_WIDTH-1:0] result
);

    always @(*) begin
        case (op)
            4'b0001: result = src1 + src2;
            default: result = 0;
        endcase
    end

endmodule
