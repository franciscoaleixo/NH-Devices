import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import (
    CONF_ID,
    CONF_INVERTED,
    CONF_MODE,
    CONF_PULLUP,
    CONF_PULLDOWN,
    CONF_NUMBER,
)
from esphome.components import binary_sensor
from esphome import pins
from ..nh_alcv5t24 import NHALCV5T24Component, CONF_CONTROLLER_KEY

# Metadata
CODEOWNERS = ["@franciscoaleixo"]

CONF_NHALCV5T24_BINARY_SENSOR = "nh_alcv5t24_binary_sensor"

CONF_NHALCV5T24_SENSOR_PIN = "sensor_pin"

# Namespace / Component
binary_sensor_ns = cg.esphome_ns.namespace("nh_alcv5t24").namespace(CONF_NHALCV5T24_BINARY_SENSOR)
BinarySensorComponent = binary_sensor_ns.class_("BinarySensor", binary_sensor.BinarySensor, cg.Component)

# Custom Pin for simple binary sensors
BinarySensorPin = binary_sensor_ns.class_("BinarySensorPin", cg.GPIOPin)

NHALCV5T24_BINARY_PIN_SCHEMA = cv.All(
    {
        cv.GenerateID(): cv.declare_id(BinarySensorPin),
        cv.Required(CONF_NUMBER): cv.int_range(min=1, max=2),
        cv.Optional(CONF_MODE, default={}): cv.All(
            {
                cv.Optional(CONF_PULLUP, default=False): cv.boolean,
                cv.Optional(CONF_PULLDOWN, default=False): cv.boolean,
            }
        ),
        cv.Optional(CONF_INVERTED, default=False): cv.boolean,
    }
)

@pins.PIN_SCHEMA_REGISTRY.register(CONF_NHALCV5T24_BINARY_SENSOR, NHALCV5T24_BINARY_PIN_SCHEMA)
async def nhalcv5t24_binary_sensor_pin_to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_parented(var, config[CONF_NHALCV5T24_BINARY_SENSOR])
    
    cg.add(var.set_pin(config[CONF_NUMBER]))
    cg.add(var.set_inverted(config[CONF_INVERTED]))
    cg.add(var.set_flags(pins.gpio_flags_expr(config[CONF_MODE])))
    return var


# Main binary sensor
CONFIG_SCHEMA = binary_sensor.BINARY_SENSOR_SCHEMA.extend({
  cv.GenerateID(): cv.declare_id(BinarySensorComponent),
  cv.Required(CONF_CONTROLLER_KEY): cv.use_id(NHALCV5T24Component),
  cv.Required(CONF_NHALCV5T24_SENSOR_PIN): NHALCV5T24_BINARY_PIN_SCHEMA,
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    controller = await cg.get_variable(config[CONF_CONTROLLER_KEY])

    var = await binary_sensor.new_binary_sensor(config)
    await cg.register_component(var, config)

    sensor_pin = await cg.gpio_pin_expression(config[CONF_NHALCV5T24_SENSOR_PIN])

    cg.add(var.set_sensor_pin(sensor_pin))
    cg.add(controller.register_sensor(var))