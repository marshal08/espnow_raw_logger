import esphome.codegen as cg

espnow_raw_logger_ns = cg.esphome_ns.namespace("espnow_raw_logger")
ESPNowRawLogger = espnow_raw_logger_ns.class_("ESPNowRawLogger", cg.Component)

def to_code(config):
    cg.add(ESPNowRawLogger().set_id("espnow_raw_logger"))
