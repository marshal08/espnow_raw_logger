import esphome.codegen as cg

espnow_ns = cg.esphome_ns.namespace("espnow_raw_logger")
ESPNowRawLogger = espnow_ns.class_("ESPNowRawLogger", cg.Component)

CONFIG_SCHEMA = cg.Schema({}).extend({})

async def to_code(config):
    cg.add(ESPNowRawLogger())

# 👇 Register the YAML block with the component class
espnow_raw_logger = ESPNowRawLogger()
cg.register_component(espnow_raw_logger)
