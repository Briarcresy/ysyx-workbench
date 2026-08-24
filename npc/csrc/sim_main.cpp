#include <VminirvCPU.h>
#include <cstdint>
#include <cstdio>

static VminirvCPU dut;
static uint32_t instr_mem[1u << 15] = {
    0x00500093, // addi x1, x0,  5
    0xffe08113, // addi x2, x1, -2
    0x00100013, // addi x0, x0,  1 (x0 must remain 0)
};

static uint32_t pmem_read(uint32_t pc)
{
    return instr_mem[pc >> 2];
}

static void print()
{
    std::printf("pc = 0x%08" PRIx32 ", inst = 0x%08" PRIx32,
        static_cast<uint32_t>(dut.pc),
        static_cast<uint32_t>(dut.inst));
    if (dut.debug_wb_we) {
        std::printf(", x%" PRIx32 " <- 0x%08" PRIx32,
            static_cast<uint32_t>(dut.debug_wb_rd),
            static_cast<uint32_t>(dut.debug_wb_data));
    }
    std::putchar('\n');
}

static void single_cycle()
{
    dut.inst = pmem_read(dut.pc);
    dut.clk = 0;
    dut.eval();

    print();

    dut.clk = 1;
    dut.eval();
}

static void reset()
{
    dut.rst = 1;
    single_cycle();
    dut.rst = 0;
}

int main()
{
    reset();
    for (int i = 0; i < 3; ++i) {
        single_cycle();
    }
    print();
    dut.final();
    return 0;
}
