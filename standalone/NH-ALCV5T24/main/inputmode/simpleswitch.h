#ifndef SIMPLESWITCH_H
#define SIMPLESWITCH_H

#include "inputmode.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/portmacro.h"

namespace simple_switch_input_mode {
    typedef struct {
        gpio_num_t gpio_nr;
        void (*on_input_switch_change)(bool);
    } simple_switch_args;
}

using namespace simple_switch_input_mode;

static inline void IRAM_ATTR simple_switch_interrupt_handler(void *args);
static inline void simple_switch_control_task(void *params);

class SimpleSwitchInputMode : public InputMode {
    public:
        SimpleSwitchInputMode(simple_switch_args *switch_args) { args = switch_args; }; 
        void initialize();
        const char* get_description();

    private:
        simple_switch_args *args;
};

#endif