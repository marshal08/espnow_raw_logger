import esphome.codegen as cg

espnow_ns = cg.esphome_ns.namespace("espnow_raw_logger")
ESPNowRawLogger = espnow_ns.class_("ESPNowRawLogger", cg.Component)

CONFIG_SCHEMA = cg.Schema({})

async def to_code(config):
    var = cg.new_Pvariable(config.get("id", "espnow_raw_logger"))
    cg.add(var)
