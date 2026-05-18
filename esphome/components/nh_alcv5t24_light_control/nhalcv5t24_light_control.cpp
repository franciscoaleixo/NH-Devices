#include "esphome/core/log.h"
#include "nhalcv5t24_light_control.h"

namespace esphome {
    namespace nh_alcv5t24 {
        namespace nh_alcv5t24_light_control {
            static const char *TAG = "nh_alcv5t24_light_control";

            // See https://github.com/espressif/esp-idf/blob/b3f7e2c8a4d354df8ef8558ea7caddc07283a57b/examples/storage/nvs_rw_value/main/nvs_value_example_main.c
            void LightControl::setup(){
                this->publish_state(this->initialValue);
                on_number_change_callback(this->state, get_control_type());
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