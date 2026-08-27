#include <VminirvCPU.h>
#include <VminirvCPU__Dpi.h>
#include <cstdint>
#include <cstdio>

#define PMEM_SIZE (1u << 20)

static VminirvCPU dut;
static uint8_t pmem[PMEM_SIZE];

static bool halt = false;

extern "C" int pmem_read(int raddr)
{
    // 总是读取地址为`raddr & ~0x3u`的4字节返回
    const int offset = raddr & ~0x3u;
    return pmem[offset + 0] | pmem[offset + 1] << 8 | pmem[offset + 2] << 16 | pmem[offset + 3] << 24;
}
extern "C" void pmem_write(int waddr, int wdata, char wmask)
{
    const int offset = waddr & ~0x3u;
    if (wmask & 0x1)
        pmem[offset + 0] = wdata & 0xff;
    if (wmask & 0x2)
        pmem[offset + 1] = (wdata >> 8) & 0xff;
    if (wmask & 0x4)
        pmem[offset + 2] = (wdata >> 16) & 0xff;
    if (wmask & 0x8)
        pmem[offset + 3] = (wdata >> 24) & 0xff;
    // 总是往地址为`waddr & ~0x3u`的4字节按写掩码`wmask`写入`wdata`
    // `wmask`中每比特表示`wdata`中1个字节的掩码,
    // 如`wmask = 0x3`代表只写入最低2个字节, 内存中的其它字节保持不变
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
    std::printf("npc_trap: pc = 0x%08" PRIx32 ", inst = 0x%08" PRIx32 "\n",
        static_cast<uint32_t>(dut.pc),
        static_cast<uint32_t>(dut.inst));
    halt = true;
}

bool load_image(const char* filename)
{
    FILE* fp = std::fopen(filename, "rb");
    assert(fp != nullptr);
    std::fread(pmem, 1, sizeof(pmem), fp);
    std::fclose(fp);
    return true;
}

int main()
{
    load_image("/home/briarcresy/ysyx/ysyx-workbench/npc/images/mem.bin");
    // halt at 0x00001218
    // ebreak : 0x00100073
    pmem[0x1218] = 0x73;
    pmem[0x1219] = 0x00;
    pmem[0x121a] = 0x10;
    pmem[0x121b] = 0x00;
    reset();
    while (!halt) {
        single_cycle();
    }
    dut.final();
    return 0;
}
