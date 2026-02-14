#pragma once
#include "pox/types.hpp"
#include <vector>
#include <string>

namespace pox::util {

// Very small serialization helpers for state snapshots.
// This is intentionally minimal and deterministic.

struct BlobWriter {
  std::vector<u8> data;
  void write_u8(u8 v) { data.push_back(v); }
  void write_u16(u16 v);
  void write_u32(u32 v);
  void write_u64(u64 v);
  void write_bytes(const void* p, size_t n);
};

struct BlobReader {
  const u8* p = nullptr;
  size_t n = 0;
  size_t o = 0;

  u8  read_u8();
  u16 read_u16();
  u32 read_u32();
  u64 read_u64();
  void read_bytes(void* out, size_t bytes);
};

} // namespace pox::util
