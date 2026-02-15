# P-O-X Handheld — Unified RF, WiFi, and Internet API Design

This document provides a unified API and code architecture for supporting RF, WiFi, and Internet multiplayer and data exchange in a P-O-X handheld clone or emulator.

---

## 1. API Overview
- **Goal:** Seamless multiplayer, trading, and data sync over RF, WiFi, or Internet.
- **Unified Packet:** `[0xAA][DeviceID][Type][Payload][Checksum]`
- **Fallback:** Internet → WiFi → RF
- **Abstracted API:** Same function calls for all transports.

---

## 2. Core API Functions
```cpp
// Initialize all wireless systems
void wireless_init();

// Send a packet (auto-selects best available transport)
bool wireless_send(const Packet& pkt);

// Receive a packet (blocking or with timeout)
bool wireless_receive(Packet& pkt, int timeout_ms = 1000);

// Get current connection type (RF, WiFi, Internet)
ConnectionType wireless_get_connection_type();

// Set device ID
void wireless_set_device_id(uint8_t id);

// Register event callback (for async events)
void wireless_on_event(void (*callback)(const Packet&));
```

---

## 3. Packet Structure
```cpp
struct Packet {
  uint8_t header;      // 0xAA
  uint8_t deviceID;
  uint8_t type;        // 0x01=Battle, 0x02=Infect, 0x03=Sync, etc.
  uint8_t payload[8];  // Custom data
  uint8_t checksum;    // Sum of all bytes modulo 256
};
```

---

## 4. ConnectionType Enum
```cpp
enum class ConnectionType {
  RF,
  WiFi,
  Internet,
  None
};
```

---

## 5. Example Usage
```cpp
wireless_init();
wireless_set_device_id(0x42);
Packet pkt = {0xAA, 0x42, 0x01, {0}, 0};
pkt.checksum = calcChecksum(pkt);
wireless_send(pkt);
Packet resp;
if (wireless_receive(resp, 2000)) {
  // Handle response
}
```

---

## 6. Implementation Notes
- **RF:** Use nRF24L01+ or similar, as in RF_COMMUNICATION.md
- **WiFi:** Use UDP/TCP sockets, mDNS for discovery
- **Internet:** Use HTTP/WebSocket client
- **Auto-Fallback:** Try Internet, then WiFi, then RF
- **Async Events:** Use callbacks for incoming packets

---

## 7. Security
- Device authentication for Internet
- Encrypted packets for WiFi/Internet
- Parental controls for online play

---

## 8. Extending the API
- Add support for Bluetooth, LoRa, or other transports
- Add cloud save, leaderboard, and OTA update endpoints

---

## 9. References
- See docs/RF_COMMUNICATION.md and docs/WIRELESS_AND_INTERNET.md for protocol and hardware details
