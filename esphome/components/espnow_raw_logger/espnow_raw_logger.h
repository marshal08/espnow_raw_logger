#pragma once

#include "esphome/core/component.h"
#include "esphome/components/text_sensor/text_sensor.h"

namespace esphome {
namespace espnow_raw_logger {

class ESPNowRawLogger : public esphome::Component {

 public:
  void setup() override;
  void on_data_recv(const uint8_t *mac_addr, const uint8_t *data, int len);

  text_sensor::TextSensor *topic_sensor{nullptr};
  text_sensor::TextSensor *payload_sensor{nullptr};
};

}  // namespace espnow_raw_logger
}  // namespace esphome
