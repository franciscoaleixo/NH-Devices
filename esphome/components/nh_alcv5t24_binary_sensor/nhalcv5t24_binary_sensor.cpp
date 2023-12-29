#include "nhalcv5t24_binary_sensor.h"
#include "esphome/core/log.h"

namespace esphome {
    namespace nh_alcv5t24 {
        namespace nh_alcv5t24_binary_sensor {
            static const char *TAG = "nh_alcv5t24_binary_sensor";

            void BinarySensor::dump_config() {
                ESP_LOGCONFIG(TAG, "Test");
            }
        } // namespace nh_alcv5t24_binary_sensor
    } // namespace nh_alcv5t24
} // namespace esphome