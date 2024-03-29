#pragma once

#include "driver/ledc.h"
#include "hal/ledc_types.h"

class PwmLightController {
    public:
        PwmLightController(gpio_num_t gpio) { gpio_nr = gpio; }; 

        void initialize();

        void change_state(bool enable);
        void change_on_value(float onVal) {
            onValue = onVal;
            adjust_lights();
        }
        void change_off_value(float offVal) {
            offValue = offVal;
            adjust_lights();
        }

        bool get_current_state() {
            return currentState;
        }
        const char* get_description();
    private:
        bool currentState = false;
        float onValue = 1.0;
        float offValue = 0.0;

        gpio_num_t gpio_nr;
        int fade_time_ms = 1000;
        // To check if it suports the duty res / freq combination:
        // div = (BASE_FREQ << 8) / (LED_FREQ * 2^(DUTY_RES)) 
        // div > 255 && div <= 262143
        // Example: 
        //   For RC_FAST_CLC (40MHz), LED_FREQ=30KHz, DUTY_RES=10bits
        //   div = 333.33, which is bigger than 255, so it's supported.
        ledc_timer_config_t ledc_conf;
        ledc_channel_config_t ledc_channel;

        void adjust_lights();

        // Converts 0..1 target duty cycle to an adjusted duty resolution duty cycle
        int get_adj_duty_cycle(float target) {
            return static_cast<int>(target * (1 << ledc_conf.duty_resolution) + 0.5);
        }
};