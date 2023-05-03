#ifndef RAM_H
#define RAM_H

#include "memory.h"

class RAM : public Memory {
    public:
    word code_segment[storage_volume] = {0};
    word data_segment[storage_volume] = {0};
    void initialize (std::string filepath);

    word* read(word ip) {
        return &code_segment[ip];
    };
    
    void write(word* dest, word value) {
        data_segment[*dest] = value;
    };

    word* read_data (word* address);
};

#endif //RAM_H