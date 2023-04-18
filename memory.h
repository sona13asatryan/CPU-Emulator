#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <string>
#include <fstream>

typedef unsigned int word;
typedef unsigned char byte;
const int storage_volume = 256;
class Memory {
    public:
    virtual word* read(word) = 0;
    virtual word* read_data(word*) = 0;
    virtual void write(word*, word) = 0;
    virtual void initialize (std::string filepath) = 0;
};


class RAM : public Memory {
    public:
    word code_segment[storage_volume] = {0};
    word data_segment[storage_volume] = {0};
    void initialize (std::string filepath) {
        std::ifstream fin(filepath, std::ios::binary);
        if (!fin.is_open()) {
            std::cerr << "Problem occured. File can't be opened!" << std::endl;
            abort();
        } 
        if (!fin) {
            std::cout << "Problem occured. Can't determine file's length!";
        }

        fin.seekg (0, std::ios::end);
        int length = fin.tellg();
        fin.seekg (0, std::ios::beg);

        fin.read((char*)code_segment, length);
        fin.close();
    }

    word* read(word ip) {
        return &code_segment[ip];
    };
    void write(word* dest, word value) {
        data_segment[*dest] = value;
    };

    word* read_data (word* address) {
        if (*address < 0 || *address > storage_volume) {
            std::cerr << "Invalid address while accessing data segment" << std::endl;
        }
        return &data_segment[*address]; 
    }
};

#endif //MEMORY_H
