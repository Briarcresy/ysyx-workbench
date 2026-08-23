module PC (
    input clk,
    input rst,
    input [3:0] jp_addr,
    input jp,
    output reg [3:0] addr
);

    always @(posedge clk) begin
        if (rst) begin
            addr <= 4'b0000;
        end else if (jp) begin
            addr <= jp_addr;
        end else begin
            addr <= addr + 4'b0001;
        end
    end

endmodule
