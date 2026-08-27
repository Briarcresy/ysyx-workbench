module LSU #(
    DATA_WIDTH = 32
) (
    input                       valid,
    input                       wen,
    input      [           2:0] funct3,
    input      [DATA_WIDTH-1:0] addr,
    input      [DATA_WIDTH-1:0] store_data,
    output reg [DATA_WIDTH-1:0] load_data
);

    wire [DATA_WIDTH-1:0] raw_rdata, shifted_rdata;
    reg  [3:0] mem_wmask;

    wire [1:0] byte_shift;
    wire [4:0] bit_shift;

    assign byte_shift = addr[1:0], bit_shift = {addr[1:0], 3'b000};
    assign shifted_rdata = raw_rdata >> bit_shift;

    DataMem #(
        .DATA_WIDTH(DATA_WIDTH)
    ) data_mem (
        .valid(valid),
        .wen  (wen),
        .waddr(addr),
        .wdata(store_data),
        .wmask(mem_wmask),
        .raddr(addr),
        .rdata(raw_rdata)
    );

    always @(*) begin
        case (funct3[1:0])
            2'b00:   mem_wmask = 4'b0001 << byte_shift;  // sb
            2'b01:   mem_wmask = 4'b0011 << byte_shift;  // sh
            2'b10:   mem_wmask = 4'b1111;  // sw
            default: mem_wmask = 4'b0000;
        endcase
    end

    always @(*) begin
        case (funct3)
            3'b000:  load_data = {{24{shifted_rdata[7]}}, shifted_rdata[7:0]};  // lb
            3'b001:  load_data = {{16{shifted_rdata[15]}}, shifted_rdata[15:0]};  // lh
            3'b010:  load_data = shifted_rdata;  // lw
            3'b100:  load_data = {24'b0, shifted_rdata[7:0]};  // lbu
            3'b101:  load_data = {16'b0, shifted_rdata[15:0]};  // lhu
            default: load_data = {DATA_WIDTH{1'b0}};
        endcase
    end

endmodule
