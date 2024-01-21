#include "esphome/core/log.h"
#include "nhalcv5t24_light_control.h"

namespace esphome {
    namespace nh_alcv5t24 {
        namespace nh_alcv5t24_light_control {
            static const char *TAG = "nh_alcv5t24_light_control";

            void LightControl::setup(){
                // this->publish_state(this->initialValue);
                // on_number_change_callback(this->state, get_control_type());
            }

            void LightControl::loop(){}

            void LightControl::control(float state) {
                this->publish_state(state);
                on_number_change_callback(state, get_control_type());
            }

            void LightControl::dump_config() {
                ESP_LOGCONFIG(TAG, "NH-ALCV5T24 Light Control");
            }

        } // namespace nh_alcv5t24_light_switch
    } // namespace nh_alcv5t24
} // namespace esphome