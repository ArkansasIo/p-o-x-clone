#pragma once
#include <cstddef>
#include <cstdint>
namespace pox::game {
uint16_t crc16_ibm(const uint8_t* data, size_t len);
}
