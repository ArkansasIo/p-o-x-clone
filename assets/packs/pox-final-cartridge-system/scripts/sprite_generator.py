# POX Procedural Sprite Generator
# Generates creature sprites for PO-X cartridges

def generate_sprites(count, output_dir):
    # TODO: Implement procedural sprite generation
    pass

if __name__ == "__main__":
    import sys
    if len(sys.argv) != 3:
        print("Usage: sprite_generator.py <count> <output_dir>")
        sys.exit(1)
    generate_sprites(int(sys.argv[1]), sys.argv[2])
