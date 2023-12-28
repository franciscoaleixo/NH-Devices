import esphome.config_validation as cv
import esphome.codegen as cg

from esphome.const import CONF_ID

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

CONF_CONTROLLER_KEY = 'controller_id'

# Schema
CONFIG_SCHEMA = cv.Schema({
  cv.GenerateID(): cv.declare_id(NHALCV5T24Component),
  cv.Required(CONF_SWITCH_SENSOR_RELATIONSHIP): cv.enum(SWITCH_SENSOR_RELATIONSHIP_OPTIONS),
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    cg.add(var.set_switch_sensor_relationship(config[CONF_SWITCH_SENSOR_RELATIONSHIP]))