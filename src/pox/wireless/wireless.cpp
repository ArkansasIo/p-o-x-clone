// Unified wireless (RF, WiFi, Internet) API implementation (stub)
#include "pox/wireless/wireless.hpp"
#include <iostream>

namespace pox::wireless {

static uint8_t device_id = 0;
static std::function<void(const Packet&)> event_callback;

void init() {
    std::cout << "[Wireless] Initialized (stub)\n";
}

bool send(const Packet& pkt) {
    std::cout << "[Wireless] Send packet type " << int(pkt.type) << "\n";
    return true;
}

bool receive(Packet& pkt, int timeout_ms) {
    std::cout << "[Wireless] Receive (stub, always false)\n";
    return false;
}

ConnectionType get_connection_type() {
    return ConnectionType::None;
}

void set_device_id(uint8_t id) {
    device_id = id;
}

void on_event(std::function<void(const Packet&)> callback) {
    event_callback = callback;
}

} // namespace pox::wireless
