#pragma once
#include "esphome/core/component.h"
#include "esphome/components/mqtt/mqtt_client.h"
#include <esp_now.h>

namespace esphome {
namespace now_mqtt_bridge {

class Now_MQTT_BridgeComponent : public Component {
 public:
  void setup() override;

  void set_wifi_channel(int channel) {
    this->wifi_channel_ = channel;
  }

 protected:
  int wifi_channel_;
};

}  // namespace now_mqtt_bridge
}  // namespace esphome
