module InstrMem (
    input [3:0] addr,
    output reg [7:0] instr
);

    reg [7:0] rom[0:15];

    initial $readmemb("/home/briarcresy/ysyx/E/E5/sCPU/images/sum.irom", rom);

    assign instr = rom[addr];

endmodule
