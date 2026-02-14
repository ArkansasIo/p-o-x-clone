// Events header for boot animation and POXC auto-mount
#pragma once

namespace pox {

struct EventFlags {
    bool boot_animation_played = false;
    bool cartridge_mounted = false;
    bool sram_loaded = false;
};

} // namespace pox
