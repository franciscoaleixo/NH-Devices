# NH-Project
Home for documentation and firmware of NH devices for home use. These devices use ESP SoCs, so for every device, there's an [esphome](https://github.com/esphome)https://github.com/esphome compatible component.

## NH-ALCV5T24
LED PWM Constant Voltage controller. The objective of this device is to control a single channel PWM LED strip (or similar) controlled by a sensing switch.

Features / characteristics:
- ESP32-C6 modules (supports both ESP32-C6-WROOM-1 and ESP32-C6-WROOM-1U).
  - Supports WiFi6 / BLE and Thread / Zigbee
- Input from 5V to 24V DC (2.1mm barrel jack)
- Sensing switch (4 pin JST-PH). Similar to STEMMA QT / Qwiic standards but with JST-PH instead of JST-SH.
- External controller support. The SoC can be skipped and every input / PWM output can be controlled through the installation of a Molex PICO EZMate connector (78171-5006)
