# Display Pipeline (PLACEHOLDER)

`Display::render_from_vram()` currently assumes:
- VRAM contains packed 2bpp pixels, 4 pixels per byte:
  bits [7:6][5:4][3:2][1:0]
- grayscale palette of 4 entries
- row-major fill into RGBA8888 framebuffer

Replace once you confirm:
- LCD width/height
- VRAM layout (tiles? bitplanes? scanlines?)
- palette / color behavior
