# C++ Asset Tools for POX Game
Dev Credit: Stephen Deline Jr

This folder contains C++ stubs for asset processing tools:

- png_quantizer.cpp: PNG quantization & 2bpp export
- wad_builder.cpp: WAD asset packer
- sram_builder.cpp: SRAM image generator
- sfx_synth.cpp: WAV SFX generator
- cartridge_packer.cpp: Cartridge packer

To implement:
- Use stb_image for PNG loading
- Standard C++ for file I/O and binary packing
- Add Bayer dithering, CRC16/IBM, CRC32 as needed


## Usage

Each tool is a command-line utility. Build them using the main CMake project or individually as needed. Run with appropriate arguments for asset conversion or packing tasks.

## Contributing

To contribute a new asset tool or feature:
- Add your C++ source file to this folder.
- Update this README with a description of your tool.
- Follow the code style and comment TODOs for clarity.
