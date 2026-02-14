#pragma once
#include "pox/types.hpp"
#include <vector>
#include <string>

namespace pox::debug {

struct TraceEntry {
  u64 cycle = 0;
  u16 pc = 0;
  u8  opcode = 0;

  u8  a = 0, x = 0, y = 0, sp = 0, flags = 0;

  bool had_mem = false;
  bool mem_write = false;
  u16 mem_addr = 0;
  u8  mem_value = 0;
};

class TraceBuffer {
public:
  void enable(bool on) { enabled_ = on; }
  bool enabled() const { return enabled_; }

  void clear();
  void push(const TraceEntry& e);
  bool dump_text(const std::string& path) const;

  const std::vector<TraceEntry>& entries() const { return entries_; }

private:
  bool enabled_ = false;
  std::vector<TraceEntry> entries_;
};

} // namespace pox::debug
