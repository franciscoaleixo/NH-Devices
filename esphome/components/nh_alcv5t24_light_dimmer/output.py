import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import CONF_ID
from esphome.components import output
from ..nh_alcv5t24 import NHALCV5T24Component, CONF_CONTROLLER_KEY

# Metadata
CODEOWNERS = ["@franciscoaleixo"]

# Namespace / Component
light_dimmer_ns = cg.esphome_ns.namespace("nh_alcv5t24").namespace('nh_alcv5t24_light_dimmer')
LightDimmerComponent = light_dimmer_ns.class_("LightDimmer", output.FloatOutput, cg.Component)


CONFIG_SCHEMA = output.FLOAT_OUTPUT_SCHEMA.extend({
  cv.GenerateID(): cv.declare_id(LightDimmerComponent),
  cv.Required(CONF_CONTROLLER_KEY): cv.use_id(NHALCV5T24Component),
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    controller = await cg.get_variable(config[CONF_CONTROLLER_KEY])

    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await output.register_output(var, config)

    cg.add(controller.register_output(var))
