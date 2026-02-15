# P-O-X Handheld — Wireless (RF, WiFi) and Internet Communication Systems

## 1. RF Communication (Legacy System)
See RF_COMMUNICATION.md for full details.
- Short-range, license-free RF (27/49/315/433/900 MHz)
- Multiplayer, infection transfer, social gameplay
- Beaconing, peer discovery, handshake, event trigger

---

## 2. WiFi System (Modern Extension)
### Purpose
- Enable multiplayer and data sync over local WiFi
- Allow internet-based battles, trading, and updates
- Bridge classic RF gameplay to modern networks

### Hardware
- ESP32 (WiFi + Bluetooth, Arduino compatible)
- Or any MCU with WiFi (ESP8266, Raspberry Pi Pico W, etc.)

### WiFi Protocol Design
- **Discovery:** mDNS/UDP broadcast for local peer discovery
- **Connection:** TCP/UDP sockets for direct peer-to-peer
- **Packet Format:**
  - `[0xAA][DeviceID][Type][Payload][Checksum]` (same as RF)
- **Sync:** Periodic beacon, handshake, event trigger
- **Fallback:** If no WiFi, use RF

### Example: ESP32 WiFi Peer Discovery (UDP)
```cpp
#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "POX_WIFI";
const char* password = "poxpass";
WiFiUDP udp;
const int port = 4210;

void setup() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  udp.begin(port);
}

void loop() {
  // Beacon
  udp.beginPacket("255.255.255.255", port);
  udp.write("POX_BEACON");
  udp.endPacket();
  delay(2000);
  // Listen for responses...
}
```

---

## 3. Internet System (Cloud Multiplayer, Updates)
### Purpose
- Enable global multiplayer, trading, and cloud saves
- Distribute firmware/game updates
- Leaderboards, stats, and social features

### Architecture
- **Device:** Connects to WiFi, authenticates with server
- **Server:** Handles matchmaking, data sync, updates
- **Protocol:**
  - REST API (HTTPS) for updates, stats, cloud saves
  - WebSockets for real-time multiplayer

### Example: REST API (Pseudo)
- `POST /api/v1/login` — Authenticate device
- `POST /api/v1/battle` — Submit battle result
- `GET /api/v1/updates` — Check for firmware/game updates
- `POST /api/v1/save` — Upload save data
- `GET /api/v1/leaderboard` — Get global rankings

### Example: ESP32 HTTP Request
```cpp
#include <WiFi.h>
#include <HTTPClient.h>

void sendBattleResult() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("https://poxcloud.example.com/api/v1/battle");
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST("{\"deviceID\":42,\"result\":\"win\"}");
    http.end();
  }
}
```

---

## 4. Unified Protocol & Fallback
- **Unified Packet:** `[0xAA][DeviceID][Type][Payload][Checksum]` for RF, WiFi, and Internet
- **Fallback Logic:**
  1. Try Internet (cloud)
  2. If not available, try WiFi peer-to-peer
  3. If not available, use RF
- **Seamless Experience:** Players can battle/trade locally or globally

---

## 5. Security & Privacy
- Device authentication (unique ID, token)
- Encrypted communication (HTTPS, WPA2)
- Parental controls for online features

---

## 6. References
- [ESP32 WiFi Library](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/wifi.html)
- [ESP32 HTTPClient](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/http.html)
- [WebSockets for ESP32](https://github.com/Links2004/arduinoWebSockets)
- [REST API Design](https://restfulapi.net/)
