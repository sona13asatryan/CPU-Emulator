#ifndef MONITOR_H
#define MONITOR_H

#include <iostream>
#include "output.h"

class Monitor : public Output {
    void write() {
        std::cout << *buffer << std::endl;
    }
};

#endif // MONITOR_H