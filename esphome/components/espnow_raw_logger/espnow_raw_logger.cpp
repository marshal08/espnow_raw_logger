#include "espnow_raw_logger.h"
#include "esphome/core/log.h"
#include <esp_now.h>
#include <WiFi.h>
#include <WiFiClient.h>

namespace esphome {
namespace espnow_raw_logger {

static const char *const TAG = "espnow_raw_logger";
static ESPNowRawLogger *global_logger = nullptr;

void ESPNowRawLogger::setup() {
  global_logger = this;

  ESP_LOGI(TAG, "Initializing ESP-NOW...");
  WiFi.mode(WIFI_STA);
  esp_now_init();

  esp_now_register_recv_cb([](const uint8_t *mac_addr, const uint8_t *data, int len) {
    if (global_logger != nullptr) {
      global_logger->on_data_recv(mac_addr, data, len);
    }
  });

  ESP_LOGI(TAG, "ESP-NOW logger ready");
}

void ESPNowRawLogger::on_data_recv(const uint8_t *mac_addr, const uint8_t *data, int len) {
  char mac_str[18];
  snprintf(mac_str, sizeof(mac_str), "%02X:%02X:%02X:%02X:%02X:%02X",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  ESP_LOGI(TAG, "Received data from %s, len=%d", mac_str, len);
}

}  // namespace espnow_raw_logger
}  // namespace esphome
