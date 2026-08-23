module ALU (
    input [7:0] A,
    input [7:0] B,
    input op,
    output reg [7:0] res
);

    always @(*) begin
        case (op)
            1'b0: res = A + B;
            1'b1: res = {7'd0, A != B};
            default: res = 8'd0;
        endcase
    end

endmodule
