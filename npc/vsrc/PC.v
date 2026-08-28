module PC #(
    DATA_WIDTH = 32
) (
    input                       clk,
    input                       rst,
    input      [DATA_WIDTH-1:0] npc,
    output reg [DATA_WIDTH-1:0] pc
);

    always @(posedge clk) begin
        if (rst) begin
            pc <= 32'h8000_0000;
        end else begin
            pc <= npc;
        end
    end

endmodule
