#include "cpu.h"
#include "argument.h"
CPU::CPU (Memory* mem, Input* in, Output* out) {
    memory = mem;
    input = in;
    output = out;
    for (int i = 0; i < reg_count; ++i) {
        regs[i] = 0;
    }
};

byte* getByte(word w, int i) {
    w = w >> (8*(3-i));
    byte* res = (byte*)&w;
    return res;
}

word CPU::fetch () {
    word instruction;
    instruction = *memory->read(*counter);
    return instruction;
}

CPU::decoded_instruction CPU::decode (word instr) {
    decoded_instruction res;
    byte byte_0 = *(getByte(instr, 0));
    byte byte_1 = *(getByte(instr, 1));
    byte byte_2 = *(getByte(instr, 2));
    byte byte_3 = *(getByte(instr, 3));
    Argument* arg;
    res.opcode = (operations)(byte_3 & 0x0F);
    res.arg1_is_imm = (byte_3 & 0x80);
    res.arg2_is_imm = (byte_3 & 0x40);
    res.arg1_is_mem = (byte_3 & 0x20);
    res.dest_is_mem = (byte_3 & 0x10);


    if (res.arg1_is_imm && res.arg1_is_mem) {
        std::cerr << "No such instruction!" << std::endl;
        abort();
    } else if (res.arg1_is_imm) {
        arg = new Imm_arg;
        res.arg1 = *arg->interprete(byte_2);
    } else if (res.arg1_is_mem) {
        arg = new Mem_arg;
        res.arg1 = *arg->interprete(byte_2, this);
    } else {
        if (byte_2 >= 0 && byte_2 < reg_count) {
            arg = new Reg_arg;
            res.arg1 = *arg->interprete(byte_2, this);
        } else if (byte_2 == reg_count) {
            res.arg1 = input->read();
        } else {
            std::cerr << "Wrong argument type (check first argument)!"<< std::endl;
            abort();
        }
    }

    if (res.arg2_is_imm) {
        arg = new Imm_arg;
        res.arg2 = *arg->interprete(byte_1);
    } else {
        if (byte_1 >= 0 && byte_1 < reg_count) {
            arg = new Reg_arg;
            res.arg2 = *arg->interprete(byte_1, this);
        } else if (byte_1 == reg_count) {
            res.arg2 = input->read();
        } else {
            std::cerr << "Wrong argument type (check second argument)!"<<std::endl;
            abort();
        }
    }

    if (res.dest_is_mem) {
        arg = new Mem_arg;
        if (byte_0 & 0x08) {
            res.dest = memory->read(byte_0);
        } else {
            res.dest = arg->interprete(byte_0, this);
        }
    } else {
        if (byte_0 >= 0 && byte_0 < reg_count) {
            arg = new Reg_arg;
            res.dest = arg->interprete(byte_0, this);
        } else if (byte_0 == reg_count) {
            res.dest_is_output = true;
            res.dest = output->buffer;
        } else {
            std::cerr << "Wrong argument type (check destination)!"<< std::endl;
            abort();
        }
    }
    return res;
}

bool CPU::execute (CPU::decoded_instruction d) {
    switch(d.opcode) {
        case operations::AND: 
            *d.dest = d.arg1 & d.arg2;
            break;
        case operations::OR:
            *d.dest = d.arg1 | d.arg2;
            break;
        case operations::NOT: 
            *d.dest = ~(d.arg1);
            break;
        case operations::NAND: 
            *d.dest = ~(d.arg1 & d.arg2);
            break;
        case operations::NOR: 
            *d.dest = ~(d.arg1 | d.arg2);
            break;
        case operations::ADD: 
            *d.dest = d.arg1 + d.arg2;
            break;
        case operations::SUB: 
            *d.dest = d.arg1 - d.arg2;
            break;
        case operations::MUL: 
            *d.dest = d.arg1 * d.arg2;
            break;
        case operations::ON: 
            *counter = *d.dest - 1;
            break;
        case operations::EQ: 
            if (d.arg1 == d.arg2) *counter = *d.dest - 1;
            break;
        case operations::GR: 
            if (d.arg1 > d.arg2) *counter = *d.dest - 1;
            break;
        case operations::GREQ: 
            if (d.arg1 >= d.arg2) *counter = *d.dest - 1;
            break;
        case operations::OFF: break;
        case operations::NEQ: 
            if (d.arg1 != d.arg2) *counter = *d.dest - 1;
            break;
        case operations::LS: 
            if (d.arg1 < d.arg2) *counter = *d.dest - 1;
            break;
        case operations::LSEQ: 
            if (d.arg1 <= d.arg2) *counter = *d.dest - 1;
            break;
    }
    if (d.dest_is_output) {
        output->write();
    }
    return 1;
}



CPU::~CPU(){};

int CPU::run() {
    while(execute(decode(fetch()))) {
        (*counter)++;
        if (*counter == storage_volume) {
            *counter = 0;
        }
    };
    return 0;
}
