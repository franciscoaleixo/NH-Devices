#ifndef MAIN_H
#define MAIN_H
#include "inputmode.h"
#include "lightcontroller.h"

namespace bootstrap {
    void print_firmware_info(InputMode* input_mode, LightController* light_controller);
}

#endif