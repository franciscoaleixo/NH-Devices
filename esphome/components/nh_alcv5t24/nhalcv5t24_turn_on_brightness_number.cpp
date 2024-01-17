#include "esphome/core/log.h"
#include "nhalcv5t24_turn_on_brightness_number.h"

namespace esphome {
    namespace nh_alcv5t24 {
        void TurnOnBrightnessNumber::control(float state) {
            this->publish_state(value);
        }
    } // namespace nh_alcv5t24
} // namespace esphome