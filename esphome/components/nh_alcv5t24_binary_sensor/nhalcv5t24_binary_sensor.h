#pragma once

#include "esphome/core/component.h"
#include "esphome/core/gpio.h"
#include "driver/gpio.h"
#include "esphome/core/hal.h"
#include "esphome/components/binary_sensor/binary_sensor.h"

namespace esphome {
    namespace nh_alcv5t24 {
        namespace nh_alcv5t24_binary_sensor {

            class BinarySensor : public binary_sensor::BinarySensor, public Component {
                public:
                    void setup() override;
                    void loop() override;
                    void dump_config() override;
                    float get_setup_priority() const override;

                    bool digital_read(int pin);
                    void set_pin_config(int pin, gpio::Flags flags);
                    void set_sensor_pin(GPIOPin *pin_) {pin = pin_; };
                protected:
                    GPIOPin *pin;
                private:
                    gpio_num_t get_gpio_pin(int pin);
            };

            class BinarySensorPin : public GPIOPin, public Parented<BinarySensor>{
                public:
                    void set_pin(uint8_t pin_) { this->pin = pin_; }
                    void set_inverted(bool inverted_) { this->inverted = inverted_; }
                    void set_flags(gpio::Flags flags_) { this->flags = flags_; }

                    void setup() override;
                    std::string dump_summary() const override;
                    void pin_mode(gpio::Flags flags) override {};
                    bool digital_read() override;
                    void digital_write(bool value) override{};

                protected:
                    uint8_t pin;
                    bool inverted;
                    gpio::Flags flags;
            };

        } // namespace nh_alcv5t24_binary_sensor
    } // namespace nh_alcv5t24
} // namespace esphome