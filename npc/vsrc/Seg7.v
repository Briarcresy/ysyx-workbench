// `timescale 1ns / 1ps
module Seg7 (
    input [3:0] dgt,
    output reg [6:0] seg
);
    // segments[6:0] = {A, B, C, D, E, F, G}, active-low
    always @(*) begin
        case (dgt)
            4'd0: seg = 7'b0000001;  // 0
            4'd1: seg = 7'b1001111;  // 1
            4'd2: seg = 7'b0010010;  // 2
            4'd3: seg = 7'b0000110;  // 3
            4'd4: seg = 7'b1001100;  // 4
            4'd5: seg = 7'b0100100;  // 5
            4'd6: seg = 7'b0100000;  // 6
            4'd7: seg = 7'b0001111;  // 7
            4'd8: seg = 7'b0000000;  // 8
            4'd9: seg = 7'b0000100;  // 9
            4'ha: seg = 7'b0001000;  // A
            4'hb: seg = 7'b1100000;  // b
            4'hc: seg = 7'b0110001;  // C
            4'hd: seg = 7'b1000010;  // d
            4'he: seg = 7'b0110000;  // E
            4'hf: seg = 7'b0111000;  // F
            default: seg = 7'b1111111;
        endcase
    end

endmodule
