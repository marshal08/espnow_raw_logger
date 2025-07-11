#include "espnow_raw_logger.h"
#include "esphome/core/log.h"

namespace esphome {
namespace now_mqtt_bridge {

static const char *const TAG = "now_mqtt_bridge";

void Now_MQTT_BridgeComponent::setup() {
  ESP_LOGI(TAG, "Initializing ESP-NOW...");

  if (esp_now_init() != ESP_OK) {
    ESP_LOGE(TAG, "ESP-NOW init failed");
    return;
  }

  esp_now_register_recv_cb([](const uint8_t *mac, const uint8_t *data, int len) {
    std::string payload(reinterpret_cast<const char *>(data), len);
    ESP_LOGI(TAG, "📥 Received: %s", payload.c_str());

    std::vector<std::string> fields;
    size_t start = 0;
    size_t end;

    while ((end = payload.find(':', start)) != std::string::npos) {
      fields.push_back(payload.substr(start, end - start));
      start = end + 1;
    }
    fields.push_back(payload.substr(start));

    if (fields.size() != 10) {
      ESP_LOGW(TAG, "Unexpected format. Got %d fields", (int)fields.size());
      return;
    }

    std::string device_name = fields[0];
    std::string device_class = fields[1];
    std::string state_class = fields[2];
    std::string sensor_name = fields[3];
    std::string unit = fields[4];
    std::string value = fields[5];
    std::string icon_prefix = fields[6];
    std::string icon = fields[7];
    std::string version = fields[8];
    std::string board = fields[9];

    std::string object_id = device_name + "_" + sensor_name;
    std::string topic_base = "homeassistant/sensor/" + object_id;

    std::string config_topic = topic_base + "/config";
    std::string state_topic = "now/" + object_id;

    mqtt::global_mqtt_client->publish(state_topic, value);

    mqtt::MQTTJsonObject json;
    json["name"] = sensor_name;
    json["unique_id"] = object_id;
    json["object_id"] = object_id;
    json["state_topic"] = state_topic;
    json["device_class"] = device_class;
    json["unit_of_measurement"] = unit;
    json["icon"] = "mdi:" + icon;
    json["state_class"] = state_class;

    mqtt::global_mqtt_client->publish_json(config_topic, json);
    ESP_LOGI(TAG, "📡 Published sensor %s → %s", object_id.c_str(), value.c_str());
  });

  ESP_LOGI(TAG, "ESP-NOW MQTT Bridge is live on channel %d", this->wifi_channel_);
}

}  // namespace now_mqtt_bridge
}  // namespace esphome
