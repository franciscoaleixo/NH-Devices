#include "esphome/core/log.h"
#include "nhalcv5t24_light_dimmer.h"

namespace esphome {
    namespace nh_alcv5t24 {
        namespace nh_alcv5t24_light_dimmer {
            static const char *TAG = "nh_alcv5t24_light_dimmer";

            void LightDimmer::setup(){}

            void LightDimmer::loop(){}

            void LightDimmer::write_state(float state) {
                on_dimmer_change_callback(state);
            }

            void LightDimmer::dump_config() {
                ESP_LOGCONFIG(TAG, "NH-ALCV5T24 Light Dimmer");
            }

        } // namespace nh_alcv5t24_light_switch
    } // namespace nh_alcv5t24
} // namespace esphome