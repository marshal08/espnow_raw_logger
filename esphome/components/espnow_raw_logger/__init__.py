import esphome.codegen as cg
import esphome.config_validation as cv
import esphome.components.text_sensor as text_sensor
from esphome.const import CONF_ID

CONF_TOPIC_SENSOR = "topic_sensor"
CONF_PAYLOAD_SENSOR = "payload_sensor"

espnow_raw_logger_ns = cg.esphome_ns.namespace("espnow_raw_logger")
ESPNowRawLogger = espnow_raw_logger_ns.class_("ESPNowRawLogger", cg.Component, cpp=False)


CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(ESPNowRawLogger),
    cv.Required(CONF_TOPIC_SENSOR): cv.use_id(text_sensor.TextSensor),
    cv.Required(CONF_PAYLOAD_SENSOR): cv.use_id(text_sensor.TextSensor),
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    logger = await cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(logger, config)
    topic = await cg.get_variable(config[CONF_TOPIC_SENSOR])
    cg.add(logger.topic_sensor.set_parent(topic))
    payload = await cg.get_variable(config[CONF_PAYLOAD_SENSOR])
    cg.add(logger.payload_sensor.set_parent(payload))
