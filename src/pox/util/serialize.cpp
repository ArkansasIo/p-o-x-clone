#include "pox/util/serialize.hpp"
#include <cstring>
#include <stdexcept>

namespace pox::util {

static void write_le(std::vector<u8>& d, u64 v, int bytes) {
  for (int i = 0; i < bytes; i++) d.push_back((u8)((v >> (8*i)) & 0xFF));
}

void BlobWriter::write_u16(u16 v) { write_le(data, v, 2); }
void BlobWriter::write_u32(u32 v) { write_le(data, v, 4); }
void BlobWriter::write_u64(u64 v) { write_le(data, v, 8); }

void BlobWriter::write_bytes(const void* p, size_t n) {
  const auto* b = (const u8*)p;
  data.insert(data.end(), b, b + n);
}

u8 BlobReader::read_u8() {
  if (o + 1 > n) throw std::runtime_error("BlobReader OOB");
  return p[o++];
}

u16 BlobReader::read_u16() {
  u16 v = 0;
  v |= (u16)read_u8();
  v |= (u16)read_u8() << 8;
  return v;
}

u32 BlobReader::read_u32() {
  u32 v = 0;
  for (int i = 0; i < 4; i++) v |= (u32)read_u8() << (8*i);
  return v;
}

u64 BlobReader::read_u64() {
  u64 v = 0;
  for (int i = 0; i < 8; i++) v |= (u64)read_u8() << (8*i);
  return v;
}

void BlobReader::read_bytes(void* out, size_t bytes) {
  if (o + bytes > n) throw std::runtime_error("BlobReader OOB");
  std::memcpy(out, p + o, bytes);
  o += bytes;
}

} // namespace pox::util
