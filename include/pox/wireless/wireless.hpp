// Unified wireless (RF, WiFi, Internet) API for POX
#pragma once
#include <cstdint>
#include <functional>

namespace pox::wireless {

struct Packet {
    uint8_t header;      // 0xAA
    uint8_t deviceID;
    uint8_t type;        // 0x01=Battle, 0x02=Infect, 0x03=Sync, etc.
    uint8_t payload[8];  // Custom data
    uint8_t checksum;    // Sum of all bytes modulo 256
};

enum class ConnectionType {
    RF,
    WiFi,
    Internet,
    None
};

void init();
bool send(const Packet& pkt);
bool receive(Packet& pkt, int timeout_ms = 1000);
ConnectionType get_connection_type();
void set_device_id(uint8_t id);
void on_event(std::function<void(const Packet&)> callback);

} // namespace pox::wireless
