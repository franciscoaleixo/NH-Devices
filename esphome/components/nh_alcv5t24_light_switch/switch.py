import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import CONF_ID
from esphome.components import switch
from ..nh_alcv5t24 import NHALCV5T24Component, CONF_CONTROLLER_KEY

# Metadata
CODEOWNERS = ["@franciscoaleixo"]

# Namespace / Component
light_switch_ns = cg.esphome_ns.namespace("nh_alcv5t24").namespace('nh_alcv5t24_light_switch')
LightSwitchComponent = light_switch_ns.class_("LightSwitch", switch.Switch, cg.Component)

CONFIG_SCHEMA = switch.SWITCH_SCHEMA.extend({
  cv.GenerateID(): cv.declare_id(LightSwitchComponent),
  cv.Required(CONF_CONTROLLER_KEY): cv.use_id(NHALCV5T24Component),
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    controller = await cg.get_variable(config[CONF_CONTROLLER_KEY])

    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await switch.register_switch(var, config)

    cg.add(controller.register_light_switch(var))
