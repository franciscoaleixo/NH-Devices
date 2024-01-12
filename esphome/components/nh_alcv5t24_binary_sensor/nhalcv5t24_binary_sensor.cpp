#include "nhalcv5t24_binary_sensor.h"
#include "esphome/core/log.h"

namespace esphome {
    namespace nh_alcv5t24 {
        namespace nh_alcv5t24_binary_sensor {

            static const char *TAG = "nh_alcv5t24_binary_sensor";

            void BinarySensor::setup() {
                // We always default to OFF until the sensor changes from the initial state
                // as an eletricity saving feature.
                this->initial_state = this->pin->digital_read();;
                this->has_initialized = false;
                this->publish_initial_state(false);
            }

            void BinarySensor::loop() {
                bool pin_state = this->pin->digital_read();
                if (has_initialized) {
                    this->publish_state(pin_state);
                } else {
                    if(initial_state != pin_state) {
                        this->has_initialized = true
                    }
                }
                
            }

            float BinarySensor::get_setup_priority() const { return setup_priority::HARDWARE; }

            void BinarySensor::dump_config() {
                ESP_LOGCONFIG(TAG, "NH-ALCV5T24 - Simple Binary Sensor");
            }

            gpio_num_t BinarySensor::get_gpio_pin(int pin) {
                switch(pin){
                    case 1:
                        return GPIO_NUM_6;
                    case 2:
                        return GPIO_NUM_7;
                        break;
                    default:
                        ESP_LOGE(TAG, "Pin must either be 1 (GPIO6) or 2 (GPIO7), defaulting to 1.");
                        return GPIO_NUM_6;
                }
            }

            void BinarySensor::set_pin_config(int pin, gpio::Flags flags) {
                gpio_num_t gpio_nr = this->get_gpio_pin(pin);

                gpio_set_direction(gpio_nr, GPIO_MODE_INPUT);

                if(flags & gpio::FLAG_PULLUP && flags & gpio::FLAG_PULLDOWN) {
                    gpio_set_pull_mode(gpio_nr, GPIO_PULLUP_PULLDOWN);
                } else if (flags & gpio::FLAG_PULLUP) {
                    gpio_set_pull_mode(gpio_nr, GPIO_PULLUP_ONLY);
                } else if (flags & gpio::FLAG_PULLDOWN) {
                    gpio_set_pull_mode(gpio_nr, GPIO_PULLDOWN_ONLY);
                }
            }

            bool BinarySensor::digital_read(int pin) {
                gpio_num_t gpio_nr = this->get_gpio_pin(pin);
                return gpio_get_level(gpio_nr) == 1;
            }


            // Binary Sensor Pin
            void BinarySensorPin::setup() {
                this->parent_->set_pin_config(this->pin, this->flags);
            }
            std::string BinarySensorPin::dump_summary() const { return str_snprintf("%u via NHALCV5T24", 15, this->pin); }
            bool BinarySensorPin::digital_read() { return this->parent_->digital_read(this->pin) != this->inverted; }
        } // namespace nh_alcv5t24_binary_sensor
    } // namespace nh_alcv5t24
} // namespace esphome