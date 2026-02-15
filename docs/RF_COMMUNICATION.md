# P-O-X Handheld (2001) — RF Communication System

## Overview
The P-O-X handheld used a short-range RF wireless link for multiplayer battles, infection/creature transfer, and social gameplay. This document covers the original system, reverse-engineered protocol, and a modern clone design (hardware, protocol, and code).

---

## 1. Original RF System (2001)
### Hardware
- **RF Transceiver:** ASK/FSK, superheterodyne or super-regenerative receiver
- **Antenna:** Internal wire or PCB trace
- **Frequency:** Likely 27/49/315/433/900 MHz (license-free bands)
- **Range:** ~30 ft (9 m)
- **Power:** <10 mW, AAA batteries

### Communication
- **Beaconing:** Device broadcasts ID packets every few seconds
- **Peer Discovery:** Nearby units respond, handshake begins
- **Packet Structure:**
  - Header
  - Device ID
  - Signal type (battle/infect/sync)
  - Creature data
  - Checksum
- **Protocol Flow:**
  1. Beacon broadcast
  2. Response/handshake
  3. Authentication
  4. Game event (battle/infection)
  5. Data sync/result

---

## 2. Reverse-Engineered Protocol (Typical)
- **Packet Example:**
  - `[0xAA][DeviceID][Type][Payload][Checksum]`
  - `Type`: 0x01 = Battle, 0x02 = Infection, 0x03 = Sync
  - `Payload`: Creature stats, infection status, etc.
- **Handshake:**
  - Device A beacons
  - Device B responds
  - Both exchange IDs
  - Event triggered
- **Error Checking:** Simple checksum (sum of bytes modulo 256)

---

## 3. Modern RF System Clone
### Hardware Options
- **nRF24L01+ (2.4 GHz, SPI, cheap, robust)**
- **CC1101 (sub-GHz, SPI, long range)**
- **ESP32 (ESP-NOW, WiFi-based, no router needed)**
- **LoRa (long range, not required for playground use)**

### Recommended: nRF24L01+
- **Pros:** Cheap, easy, Arduino/ESP32 support, low power
- **Wiring:**
  - VCC, GND, CE, CSN, SCK, MOSI, MISO
- **Libraries:**
  - Arduino: `RF24` library

---

## 4. Modern Protocol Design
- **Beacon:** Broadcast device ID every 2 seconds
- **Discovery:** Listen for beacons, respond with own ID
- **Handshake:** Exchange IDs, confirm event
- **Packet Format:**
  - `[0xAA][DeviceID][Type][Payload][Checksum]`
- **Event Types:**
  - 0x01: Battle
  - 0x02: Infection
  - 0x03: Sync
- **Payload:**
  - Creature stats, infection status, etc.
- **Checksum:** Sum of all bytes modulo 256

---

## 5. Arduino/ESP32 Example Code (nRF24L01+)
```cpp
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "POX01";

struct Packet {
  uint8_t header = 0xAA;
  uint8_t deviceID;
  uint8_t type;
  uint8_t payload[8];
  uint8_t checksum;
};

uint8_t calcChecksum(const Packet& pkt) {
  uint8_t sum = 0;
  const uint8_t* ptr = (const uint8_t*)&pkt;
  for (int i = 0; i < sizeof(Packet) - 1; ++i) sum += ptr[i];
  return sum;
}

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();
}

void loop() {
  // Beacon
  Packet pkt;
  pkt.deviceID = 0x42; // Example
  pkt.type = 0x01; // Battle
  memset(pkt.payload, 0, sizeof(pkt.payload));
  pkt.checksum = calcChecksum(pkt);
  radio.stopListening();
  radio.write(&pkt, sizeof(pkt));
  radio.startListening();
  delay(2000);
  // Listen for responses...
}
```

---

## 6. Packet Format & Handshake Logic
- **Packet:** `[0xAA][DeviceID][Type][Payload][Checksum]`
- **Handshake:**
  1. Device A beacons
  2. Device B responds
  3. Exchange IDs
  4. Confirm event
  5. Exchange data

---

## 7. RF vs IR Comparison
| Feature         | RF (P-O-X) | IR (Game Boy) |
|-----------------|------------|---------------|
| Range           | ~9 m       | ~1 m          |
| Directionality  | Omni       | Line-of-sight |
| Power           | Low        | Very low      |
| Interference    | Medium     | Low           |
| Multiplayer     | Yes        | Yes           |
| Social Play     | Yes        | Limited       |

---

## 8. References & Further Reading
- [nRF24L01+ Arduino Guide](https://tmrh20.github.io/RF24/)
- [Reverse Engineering Toy RF Protocols](https://www.rtl-sdr.com/reverse-engineering-simple-433-mhz-rf-devices/)
- [P-O-X Handheld Info](https://en.wikipedia.org/wiki/P-O-X)
