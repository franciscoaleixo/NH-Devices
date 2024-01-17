#pragma once

#include "esphome/core/component.h"
#include "esphome/core/log.h"
#include "../nh_alcv5t24_light_switch/nhalcv5t24_light_switch.h"
#include "../nh_alcv5t24_light_dimmer/nhalcv5t24_light_dimmer.h"
#include "../nh_alcv5t24_binary_sensor/nhalcv5t24_binary_sensor.h"
#include "./PwmLightController.h"


namespace esphome {
    namespace nh_alcv5t24 {
        static const char *TAG = "nh_alcv5t24";

        enum SwitchSensorRelationship { DIRECT, INVERSE, NONE };

        class NH_ALCV5T24 : public Component {
            public:
                void setup() override;
                void loop() override;
                void dump_config() override;

                void set_switch_sensor_relationship(SwitchSensorRelationship relationship) { 
                    this->switch_sensor_relationship = relationship;
                };

                void register_light_switch(nh_alcv5t24_light_switch::LightSwitch *light_switch) {
                    light_switch->set_callback([this] (bool enabled) { this->request_switch_change(enabled, DIRECT); });
                    light_switches.push_back(light_switch);
                };

                void register_sensor(nh_alcv5t24_binary_sensor::BinarySensor *sensor) {
                    sensor->add_on_state_callback([this] (bool enabled) { request_switch_change(enabled, switch_sensor_relationship); });
                    sensors.push_back(sensor);
                }

                void register_output(nh_alcv5t24_light_dimmer::LightDimmer *dimmer) {
                    if(this->light_dimmer) {
                        ESP_LOGE(TAG, "A dimmer is already registered, please register only one dimmer.");
                        return;
                    }
                    dimmer->set_callback([this] (float state) { set_turn_on_brightness(state); });
                    light_dimmer = dimmer;
                }

                void set_turn_on_brightness(float brightness){
                    this->turn_on_brightness = brightness;
                }
            protected:
                float turn_on_brightness = 1.0;

                PwmLightController light_controller = PwmLightController(GPIO_NUM_15);

                void request_switch_change(bool enabled, SwitchSensorRelationship switch_sensor_relationship);

                void request_brightness_change(float brightness);

                nh_alcv5t24_light_dimmer::LightDimmer *light_dimmer;

                std::vector<nh_alcv5t24_light_switch::LightSwitch *> light_switches;

                std::vector<nh_alcv5t24_binary_sensor::BinarySensor *> sensors;
                
                SwitchSensorRelationship switch_sensor_relationship;
        };
    }  // namespace nh_alcv5t24
}  // namespace esphome