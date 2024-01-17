#pragma once

#include "esphome/components/number/number.h"
#include "nhalcv5t24.h"

namespace esphome {
    namespace nh_alcv5t24 {
        class TurnOnBrightnessNumber : public number::Number, public Parented<NH_ALCV5T24> {
            protected:
                void control(float value) override;
        };
    } // namespace nh_alcv5t24
} // namespace esphome