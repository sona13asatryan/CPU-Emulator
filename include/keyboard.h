#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "input.h"
#include <iostream>

class Keyboard : public Input {
    word read () {
        word w;
        std::cin >> w;
        return w;
    }
};

#endif //KEYBOARD_H