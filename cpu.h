#ifndef CPU_H
#define CPU_H

#include <iostream>
#include "io.h"
#include "memory.h"


typedef unsigned int word;
typedef unsigned char byte;
const unsigned int reg_count = 16;
const unsigned int counter_id = 15;


class CPU {

    public:
    enum class operations {AND, OR, NOT, NAND, NOR, ADD, SUB, MUL,
    ON, EQ, GR, GREQ, OFF, NEQ, LS, LSEQ};

    Memory* memory;
    Input* input;
    Output* output;


    private:
        word regs[reg_count];
        word* counter = &regs[counter_id];
        
        struct decoded_instruction {
            bool arg1_is_imm;
            bool arg2_is_imm;
            bool arg1_is_mem;
            bool dest_is_mem;
            bool dest_is_output = false;
            operations opcode;
            word arg1;
            word arg2;
            word* dest;
        };

        word fetch ();
        decoded_instruction decode(word);
        bool execute(decoded_instruction);
        
    public:
    CPU(Memory*, Input*, Output*);
    ~CPU();

    word* get_reg (int n) {
        if(n >= 0 && n < reg_count-1) {
            return &regs[n];
        } else {
            std::cerr << "Reference to a non-existing register!" << std::endl;
            abort();
        }
    }
    int run();
};

#endif // CPU_H