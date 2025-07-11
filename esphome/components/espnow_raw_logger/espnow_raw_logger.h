#pragma once

#include "esphome/core/component.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include <esp_now.h>

namespace esphome {
namespace espnow_raw_logger {

class ESPNowRawLogger : public Component {
 public:
  void setup() override;
  void loop() override;

 protected:
  WiFiClient wifi_client_;
  PubSubClient mqtt_client_;
  void on_data_recv(const esp_now_recv_info_t *info, const uint8_t *data, int len);
};

}  // namespace espnow_raw_logger
}  // namespace esphome
