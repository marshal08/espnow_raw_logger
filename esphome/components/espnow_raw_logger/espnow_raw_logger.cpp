#include "espnow_raw_logger.h"
#include "esphome/core/log.h"

namespace esphome {
namespace espnow_raw_logger {

static const char *TAG = "ESPNowRawLogger";

typedef struct struct_message {
  char topic[32];
  char payload[128];
} struct_message;

struct_message incomingData;

void ESPNowRawLogger::on_data_recv(const esp_now_recv_info_t *info, const uint8_t *data, int len) {
  memcpy(&incomingData, data, sizeof(incomingData));

  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
           info->src_addr[0], info->src_addr[1], info->src_addr[2],
           info->src_addr[3], info->src_addr[4], info->src_addr[5]);

  ESP_LOGI(TAG, "ESP-NOW message received:");
  ESP_LOGI(TAG, "  From MAC: %s", macStr);
  ESP_LOGI(TAG, "  Topic: %s", incomingData.topic);
  ESP_LOGI(TAG, "  Payload: %s", incomingData.payload);

  if (mqtt_client_.connected()) {
    bool success = mqtt_client_.publish(incomingData.topic, incomingData.payload);
    ESP_LOGI(TAG, "  MQTT publish: %s", success ? "Success" : "Failed");
  } else {
    ESP_LOGW(TAG, "MQTT not connected — message not published");
  }
}

void ESPNowRawLogger::setup() {
  WiFi.mode(WIFI_STA);
  WiFi.begin("Lubo", "***");

  ESP_LOGI(TAG, "Connecting to Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    ESP_LOGI(TAG, ".");
  }

  ESP_LOGI(TAG, "Wi-Fi connected");
  ESP_LOGI(TAG, "📡 IP address: %s", WiFi.localIP().toString().c_str());

  mqtt_client_.setClient(wifi_client_);
  mqtt_client_.setServer("192.168.0.250", 1883);

  if (esp_now_init() != ESP_OK) {
    ESP_LOGE(TAG, "ESP-NOW init failed");
    return;
  }

  ESP_LOGI(TAG, "ESP-NOW initialized");
  esp_now_register_recv_cb([](const esp_now_recv_info_t *info, const uint8_t *data, int len) {
    ESPNowRawLogger *inst = static_cast<ESPNowRawLogger *>(App.get_component("espnow_raw_logger"));
    if (inst) {
      inst->on_data_recv(info, data, len);
    }
  });
}

void ESPNowRawLogger::loop() {
  if (!mqtt_client_.connected()) {
    ESP_LOGI(TAG, "Connecting to MQTT broker...");
    if (mqtt_client_.connect("ESP32S3Bridge")) {
      ESP_LOGI(TAG, "MQTT connected");
    } else {
      ESP_LOGW(TAG, "MQTT failed, rc=%d", mqtt_client_.state());
      delay(5000);
    }
  }
  mqtt_client_.loop();
}

}  // namespace espnow_raw_logger
}  // namespace esphome
