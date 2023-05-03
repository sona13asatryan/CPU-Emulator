#ifndef ARGUMENT_H
#define ARGUMENT_H

#include <iostream>
#include "memory.h"
#include "cpu.h"
#include "input.h"
#include "output.h"

class Argument {
    public:
    virtual word* interprete (byte arg, CPU* cpu = nullptr) = 0;
};

class Reg_arg : public Argument {
    public:
    word* interprete (byte arg, CPU* cpu) {
        return cpu->get_reg(arg);
    };
};

class Imm_arg : public Argument {
    public:
    word* interprete (byte arg, CPU* cpu = nullptr) {
        word* res = new word ((word)arg);
        return res;
    } 
};

class Mem_arg : public Argument {
    public:
    word* interprete (byte arg, CPU* cpu) {
        return cpu->memory->read_data((word*)(&arg));
    } 
};

#endif // ARGUMENT_H