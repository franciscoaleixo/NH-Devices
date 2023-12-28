#pragma once

#include "esphome/core/component.h"
#include "esphome/components/switch/switch.h"

namespace esphome {
    namespace nh_alcv5t24 {
        namespace nh_alcv5t24_light_switch {
            class LightSwitch : public switch_::Switch, public Component {
                public:
                    void setup() override;
                    void loop() override;
                    void dump_config() override;

                    void write_state(bool state) override;

                    void set_callback(std::function<void(bool)> callback) {
                        on_switch_change_callback = callback;
                    }
                private:
                    std::function<void(bool)> on_switch_change_callback;
            };
        } // namespace nh_alcv5t24_light_switch
    } // namespace nh_alcv5t24
} // namespace esphome