#ifndef IO_H
#define IO_H

#include <iostream>
typedef unsigned int word;

class Input {
    public:
    virtual word read() = 0; 
};

class Keyboard : public Input {
    word read () {
        word w;
        std::cin >> w;
        return w;
    }
};

class Output {
    public:
    word* buffer;
    Output() {
        buffer = new word(0);
    }
    virtual void write() = 0; 
};

class Monitor : public Output {
    void write() {
        std::cout << *buffer << std::endl;
    }
};

#endif // IO_H
