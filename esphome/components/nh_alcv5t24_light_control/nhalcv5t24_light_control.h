#pragma once

#include "esphome/core/component.h"
#include "esphome/components/number/number.h"

namespace esphome {
    namespace nh_alcv5t24 {
        namespace nh_alcv5t24_light_control {
            enum NumberControlType { TURN_ON_BRIGHTNESS, TURN_OFF_BRIGHTNESS };

            class LightControl : public number::Number, public Component {
                public:
                    void setup() override;
                    void loop() override;
                    void dump_config() override;

                    void set_control_type(NumberControlType type) {
                        controlType = type;
                    }

                    NumberControlType get_control_type() {
                        return this->controlType;
                    }

                    void set_callback(std::function<void(float, nh_alcv5t24_light_control::NumberControlType)> callback) {
                        on_number_change_callback = callback;
                    }
                    
                protected:
                    void control(float value) override;
                private:
                    NumberControlType controlType;
                    std::function<void(float, nh_alcv5t24_light_control::NumberControlType)> on_number_change_callback;
            };
        } // namespace nh_alcv5t24_light_control
    } // namespace nh_alcv5t24
} // namespace esphome