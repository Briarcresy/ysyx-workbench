module DataMem #(
    DATA_WIDTH = 32
) (
    input valid,
    input wen,
    input [DATA_WIDTH-1:0] waddr,
    input [DATA_WIDTH-1:0] wdata,
    input [3:0] wmask,
    input [DATA_WIDTH-1:0] raddr,
    output reg [DATA_WIDTH-1:0] rdata
);

    import "DPI-C" function int pmem_read(input int raddr);
    import "DPI-C" function void pmem_write(
        input int  waddr,
        input int  wdata,
        input byte wmask
    );

    always @(*) begin
        if (valid) begin  // 有读写请求时
            rdata = pmem_read(raddr);
            if (wen) begin  // 有写请求时
                pmem_write(waddr, wdata, {4'h0, wmask});
            end
        end else begin
            rdata = 0;
        end
    end

endmodule
