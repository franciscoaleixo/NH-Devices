#include "esphome/core/log.h"
#include "nhalcv5t24_light_switch.h"

namespace esphome {
    namespace nh_alcv5t24 {
        namespace nh_alcv5t24_light_switch {
            static const char *TAG = "nh_alcv5t24_light_switch";

            void LightSwitch::setup(){}

            void LightSwitch::loop(){}

            void LightSwitch::write_state(bool state) {
                on_switch_change_callback(state);
            }

            void LightSwitch::dump_config() {
                ESP_LOGCONFIG(TAG, "NH-ALCV5T24 Light Switch");
            }

        } // namespace nh_alcv5t24_light_switch
    } // namespace nh_alcv5t24
} // namespace esphome