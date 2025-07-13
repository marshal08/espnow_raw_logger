#include "espnow_raw_logger.h"
#include "esphome/core/log.h"
#include <esp_now.h>

namespace esphome {
namespace espnow_raw_logger {

static const char *const TAG = "espnow_raw_logger";
static ESPNowRawLogger *global_logger = nullptr;

void ESPNowRawLogger::setup() {
  global_logger = this;

  WiFi.mode(WIFI_STA);
  esp_err_t status = esp_now_init();
  if (status != ESP_OK) {
    ESP_LOGE(TAG, "ESP-NOW init failed: %d", status);
    return;
  }

  esp_now_register_recv_cb([](const uint8_t *mac_addr, const uint8_t *data, int len) {
    if (global_logger != nullptr) {
      global_logger->on_data_recv(mac_addr, data, len);
    }
  });

  ESP_LOGI(TAG, "🔌 ESP-NOW Bridge initialized");
}

void ESPNowRawLogger::on_data_recv(const uint8_t *mac_addr, const uint8_t *data, int len) {
  char mac_str[18];
  snprintf(mac_str, sizeof(mac_str), "%02X:%02X:%02X:%02X:%02X:%02X",
           mac_addr[0], mac_addr[1], mac_addr[2],
           mac_addr[3], mac_addr[4], mac_addr[5]);

  ESP_LOGI(TAG, "🔹 Received data from %s (len=%d)", mac_str, len);

  if (len >= 64) {
    char topic[32];
    char payload[32];
    memcpy(topic, data, sizeof(topic));
    memcpy(payload, data + sizeof(topic), sizeof(payload));

    ESP_LOGI(TAG, "📨 Topic: %s", topic);
    ESP_LOGI(TAG, "📨 Payload: %s", payload);
  } else {
    ESP_LOGW(TAG, "⚠️ ESP-NOW packet too small (%d bytes)", len);
  }
}

}  // namespace espnow_raw_logger
}  // namespace esphome
