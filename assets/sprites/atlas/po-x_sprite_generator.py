# PO-X Sprite Generator (Python)

import random
from PIL import Image

# Sprite categories and modular parts
head_types = ["single_eye", "triple_eye", "mandible", "antenna", "armored_dome", "void_mask"]
body_types = ["orb", "insectoid", "tank_chassis", "skeletal", "floating_mass", "quadruped"]
limb_types = ["claws", "spikes", "tentacles", "cannons", "blades"]
addons = ["energy_core", "dorsal_spines", "shoulder_nodes", "tail", "thrusters"]

# 8x8 sprite generator

def compose_sprite():
    img = Image.new("L", (8, 8), 0)
    pixels = img.load()
    # Random fill for demonstration
    for y in range(8):
        for x in range(8):
            if random.random() < 0.3:
                pixels[x, y] = random.choice([64, 128, 255])
    return img

# Generate 999 sprites
for i in range(999):
    sprite = compose_sprite()
    sprite.save(f"po-x_micro_{i:03}.png")

print("Generated 999 PO-X micro sprites.")
