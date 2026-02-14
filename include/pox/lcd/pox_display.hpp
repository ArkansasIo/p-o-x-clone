#pragma once
#include "pox_lcd_fb_1bpp.hpp"
#include "pox_lcd_segment_icons.hpp"
#include "pox_ui_icons.hpp"

namespace pox {
namespace lcd {

// Unified display interface for both pixel and segment LCD
class Display {
public:
    enum class Mode {
        PixelLCD,
        SegmentLCD
    };

    Display(Mode mode);
    void clear();
    void draw_sprite(const Sprite1bpp& sprite, int x, int y);
    void draw_icon(const UIIcon& icon, int x, int y);
    void set_segment_icon(const SegmentIcon& icon, int idx);
    void present(); // Push framebuffer/segments to hardware

private:
    Mode mode_;
    Framebuffer1bpp fb_;
    SegmentIconPack segment_icons_;
    UIIconPack ui_icons_;
};

} // namespace lcd
} // namespace pox
