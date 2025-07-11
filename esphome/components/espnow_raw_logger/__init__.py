import esphome.codegen as cg

espnow_raw_logger_ns = cg.new_namespace("espnow_raw_logger")
ESPNowRawLogger = espnow_raw_logger_ns.class_("ESPNowRawLogger", cg.Component)

def to_code(config):
    yield ESPNowRawLogger().init()
