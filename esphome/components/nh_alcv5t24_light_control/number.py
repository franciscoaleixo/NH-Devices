import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import CONF_ID
from esphome.components import number
from ..nh_alcv5t24 import NHALCV5T24Component, CONF_CONTROLLER_KEY

# Metadata
CODEOWNERS = ["@franciscoaleixo"]

# Namespace / Component
light_control_ns = cg.esphome_ns.namespace("nh_alcv5t24").namespace('nh_alcv5t24_light_control')
LightControlComponent = light_control_ns.class_("LightControl", number.Number, cg.Component)

# Atributes
NUMBER_CONTROL_TYPE =  light_control_ns.enum("NumberControlType")
NUMBER_CONTROL_TYPE_OPTIONS = {
    "TurnOnBrightness": NUMBER_CONTROL_TYPE.TURN_ON_BRIGHTNESS,
    "TurnOffBrightness": NUMBER_CONTROL_TYPE.TURN_OFF_BRIGHTNESS,
}
CONF_NUMBER_CONTROL_TYPE = "control_type"

CONFIG_SCHEMA = number.number_schema(LightControlComponent).extend({
        cv.GenerateID(): cv.declare_id(LightControlComponent),
        cv.Required(CONF_CONTROLLER_KEY): cv.use_id(NHALCV5T24Component),
        cv.Required(CONF_NUMBER_CONTROL_TYPE): cv.enum(NUMBER_CONTROL_TYPE_OPTIONS),
    }
).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    controller = await cg.get_variable(config[CONF_CONTROLLER_KEY])

    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await number.register_number(
        var, 
        config,
        min_value=0,
        max_value=1, 
        step=0.01
    )
    cg.add(var.set_control_type(config[CONF_NUMBER_CONTROL_TYPE]))

    cg.add(controller.register_number_control(var))
