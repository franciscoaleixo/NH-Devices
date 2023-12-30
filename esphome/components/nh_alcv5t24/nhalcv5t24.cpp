#include "nhalcv5t24.h"
#include "esphome/core/log.h"
#include "esp_chip_info.h"
#include "esp_flash.h"

namespace esphome {
    namespace nh_alcv5t24 {
        static const char *TAG = "nh_alcv5t24";

        void NH_ALCV5T24::setup() {
            light_controller.initialize();
        }

        void NH_ALCV5T24::request_switch_change(bool enabled, SwitchSensorRelationship switch_sensor_relationship) {
            bool status = enabled;
            switch(switch_sensor_relationship) {
                case DIRECT:
                    light_controller.change_state(status);
                    break;
                case INVERSE:
                    status = !enabled;
                    light_controller.change_state(status);
                    break;
                case NONE:
                    break;
            }
            // Propagate the state
            
            bool light_state = light_controller.get_current_state();
            printf("Propagating state: %s", light_state ? "true " : "false");
            for(nh_alcv5t24_light_switch::LightSwitch *light_switch : light_switches) {
                printf("Propagating state to lightswitch");
                light_switch->publish_state(light_state);
            }
        }

        void NH_ALCV5T24::loop() {}

        void NH_ALCV5T24::dump_config() {
            ESP_LOGCONFIG(TAG, "NH-ALCV5T24 V1 for Rev. A1 - LED PWM Constant Voltage controller - https://github.com/franciscoaleixo/NH-Project");
            // Print chip information
            esp_chip_info_t chip_info;
            uint32_t flash_size;
            esp_chip_info(&chip_info);
            ESP_LOGCONFIG(TAG, " --- Chip: %s with %d CPU core(s), WiFi%s%s%s, ",
                CONFIG_IDF_TARGET,
                chip_info.cores,
                (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
                (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "",
                (chip_info.features & CHIP_FEATURE_IEEE802154) ? ", 802.15.4 (Zigbee/Thread)" : "");

            unsigned major_rev = chip_info.revision / 100;
            unsigned minor_rev = chip_info.revision % 100;
            ESP_LOGCONFIG(TAG, "silicon revision v%d.%d, ", major_rev, minor_rev);

            if(esp_flash_get_size(NULL, &flash_size) != ESP_OK) {
                ESP_LOGE(TAG, "Get flash size failed");
                return;
            }
            ESP_LOGCONFIG(TAG, "%" PRIu32 "MB %s flash\n", flash_size / (uint32_t)(1024 * 1024),
                (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

            ESP_LOGCONFIG(TAG, "Minimum free heap size: %" PRIu32 " bytes ---\n", esp_get_minimum_free_heap_size());
        }

    } // namespace nh_alcv5t24
} // namespace esphome