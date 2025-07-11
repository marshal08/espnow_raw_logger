import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, mqtt
from esphome.const import (
    CONF_ID,
)
from esphome.core import coroutine_with_priority, CORE

espnow_raw_logger_ns = cg.esphome_ns.namespace("espnow_raw_logger")
ESPNowRawLogger = espnow_raw_logger_ns.class_("ESPNowRawLogger", cg.Component)

CONFIG_SCHEMA = cv.Schema({}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable("espnow_raw_logger", ESPNowRawLogger)
    await cg.register_component(var, config)
