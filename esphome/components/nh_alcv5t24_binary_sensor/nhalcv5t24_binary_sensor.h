#pragma once

#include "esphome/core/component.h"
#include "esphome/components/binary_sensor/binary_sensor.h"

namespace esphome {
    namespace nh_alcv5t24 {
        namespace nh_alcv5t24_binary_sensor {
            class BinarySensor : public binary_sensor::BinarySensor, public Component {
                public:
                    void setup() override;
                    void dump_config() override;
            };
        } // namespace nh_alcv5t24_binary_sensor
    } // namespace nh_alcv5t24
} // namespace esphome