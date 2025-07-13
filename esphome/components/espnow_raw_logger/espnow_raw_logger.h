#pragma once

#include "esphome/core/component.h"
#include <PubSubClient.h>

namespace esphome {
namespace espnow_raw_logger {

class ESPNowRawLogger : public Component {
 public:
  void setup() override;
  void on_data_recv(const uint8_t *mac_addr, const uint8_t *data, int len);

 protected:
  WiFiClient wifi_client_;
  PubSubClient mqtt_client_;
};

}  // namespace espnow_raw_logger
}  // namespace esphome
