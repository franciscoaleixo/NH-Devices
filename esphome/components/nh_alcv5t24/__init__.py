import esphome.config_validation as cv
import esphome.codegen as cg

from esphome.const import (
    CONF_ID,
    DEVICE_CLASS_ILLUMINANCE,
    ENTITY_CATEGORY_CONFIG,
    ICON_LIGHTBULB
)
from esphome.components import output, number
# Metadata
CODEOWNERS = ["@franciscoaleixo"]

# Namespace / Component
nh_alcv5t24s_ns = cg.esphome_ns.namespace("nh_alcv5t24")
NHALCV5T24Component = nh_alcv5t24s_ns.class_("NH_ALCV5T24", cg.Component)

# Attributes
SWITCH_SENSOR_RELATIONSHIP = nh_alcv5t24s_ns.enum("SwitchSensorRelationship")
SWITCH_SENSOR_RELATIONSHIP_OPTIONS = {
    "Direct": SWITCH_SENSOR_RELATIONSHIP.DIRECT,
    "Inverse": SWITCH_SENSOR_RELATIONSHIP.INVERSE,
    "None": SWITCH_SENSOR_RELATIONSHIP.NONE,
}
CONF_SWITCH_SENSOR_RELATIONSHIP = 'switch_sensor_relationship'

CONF_TURN_ON_BRIGHTNESS = "turn_on_brightness"
TurnOnBrightnessNumber = nh_alcv5t24s_ns.class_("TurnOnBrightnessNumber", number.number)

CONF_OUTPUT = "output"

CONF_CONTROLLER_KEY = 'controller_id'

# Schema
CONFIG_SCHEMA = cv.Schema({
  cv.GenerateID(): cv.declare_id(NHALCV5T24Component),
  cv.Required(CONF_SWITCH_SENSOR_RELATIONSHIP): cv.enum(SWITCH_SENSOR_RELATIONSHIP_OPTIONS),
  #cv.Optional(CONF_TURN_ON_BRIGHTNESS, default=1.0): cv.percentage,
  cv.Optional(CONF_TURN_ON_BRIGHTNESS): number.number_schema(
            TurnOnBrightnessNumber,
            device_class=DEVICE_CLASS_ILLUMINANCE,
            entity_category=ENTITY_CATEGORY_CONFIG,
            icon=ICON_LIGHTBULB,
        ),
  #cv.Optional(CONF_OUTPUT): cv.use_id(output.FloatOutput),
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    cg.add(var.set_switch_sensor_relationship(config[CONF_SWITCH_SENSOR_RELATIONSHIP]))

    n = await number.new_number(config[CONF_TURN_ON_BRIGHTNESS], min_value=0, max_value=1, step=0.01)
    await cg.register_parented(var, n)
    cg.add(var.set_turn_on_brightness(n))