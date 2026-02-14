# POX Final Cartridge System (Everything)

This bundle completes the **asset → WAD → SRAM → Cartridge (POXC)** pipeline.

## What you get
- **Web exporter** (HTML/CSS/JS): load PNG → quantize to 4-shade LCD → export 2bpp + tiles + WAD
- **Node tools** (no dependencies):
  - `wad_builder.js` — folder → `assets.wad` (PWAD lumps)
  - `save_builder.js` — generate SRAM image with 20-byte creature slots + CRC16
  - `sfx_synth.js` — generate WAV SFX (square/triangle/noise)
  - `pox_packer.js` — pack ROM + WAD + SRAM + metadata into `cartridge.poxc`
- **Boot animation** sprite sheet: `assets/boot/boot_sheet_128x64_16f.png`
- Examples in `examples/`

## Quick Start (build a cartridge)
1) Build a WAD from a folder:
```bash
node tools/node/wad_builder.js examples/wad_in examples/assets.wad
```

2) Build SRAM:
```bash
node tools/node/save_builder.js examples/save.sram 8
```

3) Pack into a cartridge:
```bash
node tools/node/pox_packer.js pack --rom path/to/main.poxr --wad examples/assets.wad --sram examples/save.sram --meta examples/metadata.json --out examples/cartridge.poxc
```

## Web Exporter
Open `tools/web_exporter/index.html` in a browser:
- Load a PNG
- Export 2bpp / tiles / WAD

## Formats
### 2bpp
4 pixels per byte:
- bits 7-6 pixel0, 5-4 pixel1, 3-2 pixel2, 1-0 pixel3

### WAD (PWAD)
Simple DOOM-style lump archive:
- header + payloads + directory

### Cartridge (POXC)
Single file that bundles:
- ROM, WAD, SRAM, metadata
with offsets in header and CRC32 integrity.
