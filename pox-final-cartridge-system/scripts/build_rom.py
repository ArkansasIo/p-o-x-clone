# POX ROM Builder Script
# Combines assets, sprites, and game data into a cartridge file

def build_rom(asset_dir, output_path):
    # TODO: Implement asset packing and binary export
    pass

if __name__ == "__main__":
    import sys
    if len(sys.argv) != 3:
        print("Usage: build_rom.py <asset_dir> <output_path>")
        sys.exit(1)
    build_rom(sys.argv[1], sys.argv[2])
