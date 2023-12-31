# NH Devices
Home for documentation and firmware of NH devices for home use. These devices use ESP SoCs. For every device there's standalone firmware and an [esphome](https://github.com/esphome) compatible component.

## NH-ALCV5T24
LED PWM Constant Voltage controller. The objective of this device is to control a single channel PWM LED strip (or similar) controlled by a sensing switch.

### Features / characteristics:
- ESP32-C6 module (supports both ESP32-C6-WROOM-1 and ESP32-C6-WROOM-1U).
  - Supports WiFi6 / BLE and Thread / Zigbee
- Input from 5V to 24V DC (2.1mm barrel jack)
- Sensing switch (4 pin JST-PH). Similar to STEMMA QT / Qwiic standards but with JST-PH instead of JST-SH.
- External controller support. The SoC can be skipped and every input / PWM output can be controlled through the installation of a Molex PICO EZMate connector (78171-5006)

### Firmware:
- For the ESP23-C6 module, you can either use the [standalone firmware](/standalone/NH-ALCV5T24/) or the [ESPHome components firmware](/esphome/components/).
- The standalone firmware does not contain any connectivity and simply deals with sensor and light turning logic.
- The ESPHome components does support connectivity and you have 3 components:
  - [components/nh_alcv5t24](/esphome/components/nh_alcv5t24/): The main component that connects everything and you can set the relationship between the sensor and the light switch.
  - [components/nh_alcv5t24_binary_sensor](/esphome/components/nh_alcv5t24/): The sensor component that connects to the board and either is sensed ON or OFF. This component in particular is meant for very basic binary sensors, i.e. uses a single input GPIO with pulldown or pullup. As of now, for more complex sensing you'd have to create your own component.
  - [components/nh_alcv5t24_light_switch](/esphome/components/nh_alcv5t24/): The switch that actually turns ON / OFF the lights. This can be triggered remotely from a HomeAssistant dashboard, and/or can be connected with the sensor above.
  - You can find an [example .yaml config here.](/esphome/nh_alcv524_example.yaml)