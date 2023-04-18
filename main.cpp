#include <iostream>
#include "cpu.h"
#include "memory.h"
#include "io.h"

int main(int argc, char ** argv){
    Memory* m = new RAM;
    m->initialize(argv[1]);
    Input* i = new Keyboard;
    Output* o = new Monitor;
    CPU ASON(m,i,o);
    ASON.run();

    return 0;
}
