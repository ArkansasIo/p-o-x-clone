#include "pox/debug/disasm.hpp"
#include <sstream>
#include <iomanip>

namespace pox::debug {

std::string disasm_one(u16 pc, u8 opcode, u8 op1, u8 op2) {
  std::ostringstream ss;
  ss << std::hex << std::setfill('0');
  ss << std::setw(4) << pc << ": ";

  switch (opcode) {
    case 0x00: ss << "NOP"; break;
    case 0x01: ss << "LDA #$" << std::setw(2) << (int)op1; break;
    case 0x02: ss << "JMP $"  << std::setw(4) << ((int)op1 | ((int)op2 << 8)); break;
    case 0x10: ss << "STA $"  << std::setw(4) << ((int)op1 | ((int)op2 << 8)); break;
    case 0x11: ss << "LDA $"  << std::setw(4) << ((int)op1 | ((int)op2 << 8)); break;
    case 0x20: ss << "ADD #$" << std::setw(2) << (int)op1; break;
    case 0x30: ss << "BRK"; break;
    default:   ss << "DB $"   << std::setw(2) << (int)opcode; break;
  }
  return ss.str();
}

} // namespace pox::debug
