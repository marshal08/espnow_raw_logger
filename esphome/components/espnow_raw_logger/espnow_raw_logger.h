#pragma once
#include "esphome/core/component.h"
#include <esp_now.h>

namespace esphome {
namespace espnow_raw_logger {

class ESPNowRawLogger : public Component {
 public:
  void setup() override {
    ESP_LOGI("espnow_raw_logger", "Initializing ESP-NOW...");
    if (esp_now_init() != ESP_OK) {
      ESP_LOGE("espnow_raw_logger", "ESP-NOW init failed");
      return;
    }

    esp_now_register_recv_cb([](const uint8_t *mac, const uint8_t *data, int len) {
      char macStr[18];
      snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
               mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

      ESP_LOGI("espnow_raw_logger", "📥 Packet from %s, length: %d", macStr, len);
      String payload;
      for (int i = 0; i < len; i++) {
        payload += (char)data[i];
      }
      ESP_LOGI("espnow_raw_logger", "📦 Payload: %s", payload.c_str());
    });
  }
};

}  // namespace espnow_raw_logger
}  // namespace esphome
