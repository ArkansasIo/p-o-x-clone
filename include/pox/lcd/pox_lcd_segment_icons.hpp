#pragma once
#include <cstdint>
#include <array>

namespace pox {
namespace lcd {

// Segment LCD icon mapping (toggleable segments)
struct SegmentIcon {
    std::array<bool, 16> segments; // Up to 16 segments per icon
};

struct SegmentIconPack {
    std::vector<SegmentIcon> icons;
};

} // namespace lcd
} // namespace pox
