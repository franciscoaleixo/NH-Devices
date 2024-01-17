import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import (
    CONF_ID,
    DEVICE_CLASS_ILLUMINANCE,
)
from esphome.components import number
from ..nh_alcv5t24 import NHALCV5T24Component, CONF_CONTROLLER_KEY

# Metadata
CODEOWNERS = ["@franciscoaleixo"]

# Namespace / Component
light_dimmer_ns = cg.esphome_ns.namespace("nh_alcv5t24").namespace('nh_alcv5t24_light_dimmer')
LightDimmerComponent = light_dimmer_ns.class_("LightDimmer", cg.Component)

TurnOnBrightnessNumber = light_dimmer_ns.class_("TurnOnBrightnessNumber", number.number)

CONF_TURN_ON_BRIGHTNESS = "turn_on_brightness"

CONFIG_SCHEMA = cv.Schema({
  cv.GenerateID(): cv.declare_id(LightDimmerComponent),
  cv.Required(CONF_CONTROLLER_KEY): cv.use_id(NHALCV5T24Component),
  cv.Required(CONF_TURN_ON_BRIGHTNESS): number.number_schema(
      TurnOnBrightnessNumber,
      device_class=DEVICE_CLASS_ILLUMINANCE
      unit_of_measurement=UNIT_PERCENT,
      entity_category=ENTITY_CATEGORY_CONFIG,
      icon=ICON_LIGHTBULB,
  ),
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    controller = await cg.get_variable(config[CONF_CONTROLLER_KEY])

    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await output.register_output(var, config)

    cg.add(controller.register_output(var))
