#include "ram.h"

void RAM::initialize (std::string filepath) {
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

word* RAM::read_data (word* address) {
    if (*address < 0 || *address > storage_volume) {
        std::cerr << "Invalid address while accessing data segment" << std::endl;
    }
    return &data_segment[*address]; 
}