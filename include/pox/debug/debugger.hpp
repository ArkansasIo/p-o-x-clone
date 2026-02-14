#pragma once
#include "pox/types.hpp"
#include <unordered_set>

namespace pox::debug {

class Debugger {
public:
  void set_enabled(bool on) { enabled_ = on; }
  bool enabled() const { return enabled_; }

  void add_breakpoint(u16 pc);
  void remove_breakpoint(u16 pc);
  bool is_breakpoint(u16 pc) const;

  void add_watch_read(u16 addr);
  void add_watch_write(u16 addr);
  bool watch_read(u16 addr) const;
  bool watch_write(u16 addr) const;

  void set_single_step(bool on) { single_step_ = on; }
  bool single_step() const { return single_step_; }

private:
  bool enabled_ = false;
  bool single_step_ = false;
  std::unordered_set<u16> bp_;
  std::unordered_set<u16> wr_;
  std::unordered_set<u16> ww_;
};

} // namespace pox::debug
