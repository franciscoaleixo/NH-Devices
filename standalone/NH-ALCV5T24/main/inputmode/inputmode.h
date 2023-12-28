#ifndef INPUTMODE_H
#define INPUTMODE_H
#include "lightcontroller.h"
#include "driver/gpio.h"

class InputMode {
    public:
        virtual void initialize() { };
        virtual const char* get_description() { return ""; };

};

#endif