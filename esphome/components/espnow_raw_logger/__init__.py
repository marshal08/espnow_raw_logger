import esphome.codegen as cg
import esphome.config_validation as cv

espnow_raw_logger_ns = cg.new_namespace("espnow_raw_logger")
ESPNowRawLogger = espnow_raw_logger_ns.class_("ESPNowRawLogger", cg.Component)

CONFIG_SCHEMA = cv.Schema({}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable("espnow_raw_logger", ESPNowRawLogger)
    await cg.register_component(var, config)
