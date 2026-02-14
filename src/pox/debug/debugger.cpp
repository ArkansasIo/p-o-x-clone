#include "pox/debug/debugger.hpp"

namespace pox::debug {

void Debugger::add_breakpoint(u16 pc) { bp_.insert(pc); }
void Debugger::remove_breakpoint(u16 pc) { bp_.erase(pc); }
bool Debugger::is_breakpoint(u16 pc) const { return bp_.find(pc) != bp_.end(); }

void Debugger::add_watch_read(u16 addr) { wr_.insert(addr); }
void Debugger::add_watch_write(u16 addr) { ww_.insert(addr); }
bool Debugger::watch_read(u16 addr) const { return wr_.find(addr) != wr_.end(); }
bool Debugger::watch_write(u16 addr) const { return ww_.find(addr) != ww_.end(); }

} // namespace pox::debug
