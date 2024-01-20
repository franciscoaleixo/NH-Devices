#pragma once

#include "esphome/core/component.h"
#include "esphome/components/number/number.h"
#include "../nh_alcv5t24/nhalcv5t24.h"

namespace esphome {
    namespace nh_alcv5t24 {
        namespace nh_alcv5t24_light_control {
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
                    
                protected:
                    void control(float value) override;
                private:
                    NumberControlType controlType;
            };
        } // namespace nh_alcv5t24_light_control
    } // namespace nh_alcv5t24
} // namespace esphome