#ifndef OUTPUT_H
#define OUTPUT_H

#include "config.h"

class Output {
    public:
    word* buffer;
    Output() {
        buffer = new word(0);
    }
    virtual void write() = 0; 
};

#endif // OUTPUT_H