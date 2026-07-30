#include <Vtop.h>
#include <nvboard.h>

#include <random>

static TOP_NAME dut;

void nvboard_bind_all_pins(TOP_NAME* top);

int random_int(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

static void single_cycle()
{
    // dut.a = random_int(0, 1);
    // dut.b = random_int(0, 1);
    dut.eval();
}

static void reset(int n)
{
    // dut.rst = 1;
    // while (n-- > 0)
    //     single_cycle();
    // dut.rst = 0;
}

int main()
{
    nvboard_bind_all_pins(&dut);
    nvboard_init();

    // reset(10);

    while (1) {
        nvboard_update();
        // single_cycle();
        dut.eval();
    }
}
