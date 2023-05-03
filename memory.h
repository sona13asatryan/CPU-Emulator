#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <string>
#include <fstream>
#include "config.h"

const int storage_volume = 256;
class Memory {
    public:
    virtual word* read(word) = 0;
    virtual word* read_data(word*) = 0;
    virtual void write(word*, word) = 0;
    virtual void initialize (std::string filepath) = 0;
};

#endif //MEMORY_H
