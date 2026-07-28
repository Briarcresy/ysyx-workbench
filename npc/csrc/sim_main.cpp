#include "Vtop.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

#include <cassert>
#include <iostream>
#include <memory>
#include <random>

int main(int argc, char** argv)
{
    const std::unique_ptr<VerilatedContext> contextp = std::make_unique<VerilatedContext>();
    contextp->commandArgs(argc, argv);

    Verilated::traceEverOn(true);
    // VerilatedVcdC* tfp = new VerilatedVcdC;
    const std::unique_ptr<VerilatedVcdC> tfp = std::make_unique<VerilatedVcdC>();

    auto top = std::make_unique<Vtop>(contextp.get());

    top->trace(tfp.get(), 1);
    tfp->open("obj_dir/simx.vcd");

    std::mt19937 generator { std::random_device { }() };
    std::uniform_int_distribution<int> bit { 0, 1 };

    while (!contextp->gotFinish()) {
        const int a = bit(generator);
        const int b = bit(generator);

        contextp->timeInc(1);

        top->a = a;
        top->b = b;
        top->eval();

        tfp->dump(contextp->time());

        // std::cout << "a = " << a
        //           << ", b = " << b
        //           << ", f = " << static_cast<int>(top->f)
        //           << '\n';
        assert(top->f == (a ^ b));
    }

    tfp->close();

    top->final();
    return 0;
}
