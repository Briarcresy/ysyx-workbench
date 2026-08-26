#include <VminirvCPU.h>
#include <VminirvCPU__Dpi.h>
#include <cstdint>
#include <cstdio>

static VminirvCPU dut;
static uint32_t instr_mem[1u << 15] = {
    0x01400513, // 0x00: addi x10, x0, 20
    0x010000e7, // 0x04: jalr x1,  x0, 16
    0x00c000e7, // 0x08: jalr x1,  x0, 12
    0x00100073, // 0x0c: ebreak
    0x00a50513, // 0x10: addi x10, x10, 10
    0x00008067, // 0x14: jalr x0,  x1, 0
};
static bool halt = false;

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
        std::printf(", x%" PRIu32 " <- %" PRIu32,
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

extern "C" void npc_trap()
{
    halt = true;
}

int main()
{
    reset();
    while (!halt) {
        single_cycle();
    }
    dut.final();
    return 0;
}
