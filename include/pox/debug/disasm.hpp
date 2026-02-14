#pragma once
#include "pox/types.hpp"
#include <string>

namespace pox::debug {

// Placeholder disassembler for the placeholder ISA.
// Replace with real PO-X opcode formatting when known.
std::string disasm_one(u16 pc, u8 opcode, u8 op1, u8 op2);

} // namespace pox::debug
