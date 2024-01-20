#pragma once

#include "esphome/core/component.h"
#include "esphome/core/log.h"
#include "../nh_alcv5t24_light_switch/nhalcv5t24_light_switch.h"
#include "../nh_alcv5t24_binary_sensor/nhalcv5t24_binary_sensor.h"
#include "./PwmLightController.h"
#include "../nh_alcv5t24_light_control/nhalcv5t24_light_control.h"


namespace esphome {
    namespace nh_alcv5t24 {
        static const char *TAG = "nh_alcv5t24";

        enum SwitchSensorRelationship { DIRECT, INVERSE, NONE };

        enum NumberControlType { TURN_ON_BRIGHTNESS, TURN_OFF_BRIGHTNESS };

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

                void register_number_control(nh_alcv5t24_light_control::LightControl *light_control){
                    control_numbers_map.insert(std::pair<NumberControlType, nh_alcv5t24_light_control::LightControl *>(light_control->get_control_type(), light_control));
                }
            protected:

                PwmLightController light_controller = PwmLightController(GPIO_NUM_15);

                void request_switch_change(bool enabled, SwitchSensorRelationship switch_sensor_relationship);

                void request_brightness_change(float brightness);

                nh_alcv5t24_light_dimmer::LightDimmer *light_dimmer;

                std::vector<nh_alcv5t24_light_switch::LightSwitch *> light_switches;

                std::vector<nh_alcv5t24_binary_sensor::BinarySensor *> sensors;
                
                SwitchSensorRelationship switch_sensor_relationship;

                std::map<NumberControlType, nh_alcv5t24_light_control::LightControl*> control_numbers_map;
        };
    }  // namespace nh_alcv5t24
}  // namespace esphome