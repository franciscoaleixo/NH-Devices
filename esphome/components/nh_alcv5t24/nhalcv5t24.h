#pragma once

#include "esphome/core/component.h"
#include "../nh_alcv5t24_light_switch/nhalcv5t24_light_switch.h"
#include "../nh_alcv5t24_sensor/nhalcv5t24_binary_sensor.h"
#include "./PwmLightController.h"


namespace esphome {
    namespace nh_alcv5t24 {
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
            protected:
                PwmLightController light_controller;

                void request_switch_change(bool enabled, SwitchSensorRelationship switch_sensor_relationship);

                std::vector<nh_alcv5t24_light_switch::LightSwitch *> light_switches;

                std::vector<nh_alcv5t24_binary_sensor::BinarySensor *> sensors;
                
                SwitchSensorRelationship switch_sensor_relationship;
        };
    }  // namespace nh_alcv5t24
}  // namespace esphome