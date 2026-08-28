#include <VminirvCPU.h>
#include <VminirvCPU__Dpi.h>
#include <assert.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ANSI_FG_RED "\33[1;31m"
#define ANSI_FG_GREEN "\33[1;32m"
#define ANSI_NONE "\33[0m"
#define ANSI_FMT(str, color) color str ANSI_NONE

static constexpr uint32_t PMEM_BASE = 0x80000000u;
static constexpr size_t PMEM_SIZE = 1u << 20;

static VminirvCPU dut;
static uint8_t pmem[PMEM_SIZE];

static bool halt = false;

static size_t guest_to_host(uint32_t address)
{
    assert(address >= PMEM_BASE && address - PMEM_BASE <= PMEM_SIZE - 4);
    return static_cast<size_t>(address - PMEM_BASE);
}

extern "C" unsigned int pmem_read(unsigned int raddr)
{
    // 总是读取地址为`raddr & ~0x3u`的4字节返回
    const uint32_t aligned_address = static_cast<uint32_t>(raddr) & ~0x3u;
    const size_t offset = guest_to_host(aligned_address);
    const uint32_t data = static_cast<uint32_t>(pmem[offset + 0]) | static_cast<uint32_t>(pmem[offset + 1]) << 8 | static_cast<uint32_t>(pmem[offset + 2]) << 16 | static_cast<uint32_t>(pmem[offset + 3]) << 24;
    return data;
}

extern "C" void pmem_write(
    unsigned int waddr,
    unsigned int wdata,
    char wmask)
{
    const uint32_t aligned_address = static_cast<uint32_t>(waddr) & ~0x3u;
    const size_t offset = guest_to_host(aligned_address);
    const uint32_t data = static_cast<uint32_t>(wdata);

    if (wmask & 0x1)
        pmem[offset + 0] = data & 0xff;
    if (wmask & 0x2)
        pmem[offset + 1] = (data >> 8) & 0xff;
    if (wmask & 0x4)
        pmem[offset + 2] = (data >> 16) & 0xff;
    if (wmask & 0x8)
        pmem[offset + 3] = (data >> 24) & 0xff;
}

static void print()
{
    printf("pc = 0x%08" PRIx32 ", inst = 0x%08" PRIx32,
        static_cast<uint32_t>(dut.pc),
        static_cast<uint32_t>(dut.inst));
    if (dut.debug_wb_we) {
        printf(", x%" PRIu32 " <- %" PRIu32,
            static_cast<uint32_t>(dut.debug_wb_rd),
            static_cast<uint32_t>(dut.debug_wb_data));
    }
    putchar('\n');
}

static void single_cycle()
{
    dut.clk = 0;
    dut.eval();

    print();

    dut.clk = 1;
    dut.eval();
}

static void reset()
{
    dut.rst = 1;
    dut.clk = 0;
    dut.eval();
    dut.clk = 1;
    dut.eval();
    dut.rst = 0;
}

extern "C" void npc_trap(int code)
{
    if (!code)
        printf(ANSI_FMT("HIT GOOD TRAP", ANSI_FG_GREEN) " at pc = 0x%08" PRIx32 "\n",
            static_cast<uint32_t>(dut.pc));
    else
        printf(ANSI_FMT("HIT BAD TRAP", ANSI_FG_RED) " at pc = 0x%08" PRIx32 ", code=%d\n",
            static_cast<uint32_t>(dut.pc), code);
    halt = true;
}

static bool load_image(const char* filename)
{
    FILE* fp = fopen(filename, "rb");
    assert(fp != nullptr);
    const size_t image_size = fread(pmem, 1, sizeof(pmem), fp);
    assert(image_size < sizeof(pmem));
    fclose(fp);
    return true;
}

int main(int argc, char** argv)
{
    assert(argc == 2);
    load_image(argv[1]);

    // halt at 0x00001218
    // ebreak : 0x00100073
    // pmem[0x1218] = 0x73;
    // pmem[0x1219] = 0x00;
    // pmem[0x121a] = 0x10;
    // pmem[0x121b] = 0x00;

    reset();
    while (!halt) {
        single_cycle();
    }
    dut.final();
    return 0;
}
