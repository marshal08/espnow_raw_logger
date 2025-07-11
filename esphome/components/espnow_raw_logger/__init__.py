import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID
from esphome.core import coroutine_with_priority

espnow_raw_logger_ns = cg.esphome_ns.namespace("espnow_raw_logger")
ESPNowRawLoggerComponent = espnow_raw_logger_ns.class_("ESPNowRawLoggerComponent", cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(ESPNowRawLoggerComponent),
})


@coroutine_with_priority(1.0)
async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
