#pragma once

#include "esphome/core/component.h"
#include "esphome/components/output/float_output.h"

namespace esphome {
    namespace nh_alcv5t24 {
        namespace nh_alcv5t24_light_dimmer {
            class LightDimmer : public output::FloatOutput, public Component {
                public:
                    void setup() override;
                    void loop() override;
                    void dump_config() override;

                    void write_state(bool state) override;

                    void set_callback(std::function<void(float)> callback) {
                        on_dimmer_change_callback = callback;
                    }
                protected:
                    void write_state(float state) override;
                private:
                    std::function<void(float)> on_dimmer_change_callback;
            };
        } // namespace nh_alcv5t24_light_dimmer
    } // namespace nh_alcv5t24
} // namespace esphome