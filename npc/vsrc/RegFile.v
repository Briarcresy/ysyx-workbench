module RegFile (
    input clk,
    input rst,
    output reg [7:0] rdata1,
    output reg [7:0] rdata2,
    input [1:0] raddr1,
    input [1:0] raddr2,
    input [1:0] waddr,
    input [7:0] wdata,
    input we
);

    reg [7:0] regs[0:3];

    assign rdata1 = regs[raddr1];
    assign rdata2 = regs[raddr2];

    always @(posedge clk) begin
        if (rst) begin
            regs[0] <= 8'b00001010;
            regs[1] <= 8'b00000000;
            regs[2] <= 8'b00000000;
            regs[3] <= 8'b00000000;
        end else if (we) begin
            regs[waddr] <= wdata;
        end
    end

endmodule
