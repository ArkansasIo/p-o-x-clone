#include "pox/debug/trace.hpp"
#include <fstream>

namespace pox::debug {

void TraceBuffer::clear() { entries_.clear(); }

void TraceBuffer::push(const TraceEntry& e) {
  if (!enabled_) return;
  entries_.push_back(e);
}

bool TraceBuffer::dump_text(const std::string& path) const {
  std::ofstream f(path);
  if (!f) return false;

  for (const auto& e : entries_) {
    f << "CYC=" << e.cycle
      << " PC=0x" << std::hex << (int)e.pc
      << " OP=0x" << std::hex << (int)e.opcode
      << " A=0x"  << std::hex << (int)e.a
      << " X=0x"  << std::hex << (int)e.x
      << " Y=0x"  << std::hex << (int)e.y
      << " SP=0x" << std::hex << (int)e.sp
      << " F=0x"  << std::hex << (int)e.flags;

    if (e.had_mem) {
      f << " MEM" << (e.mem_write ? "W" : "R")
        << "[0x" << std::hex << (int)e.mem_addr << "]=0x"
        << std::hex << (int)e.mem_value;
    }
    f << "\n";
  }
  return true;
}

} // namespace pox::debug
