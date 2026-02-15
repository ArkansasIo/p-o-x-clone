# PO-X Sprite Atlas Layout

- Micro sprites: 8x8, 999 tiles, arranged in a 37x27 grid (po-x_micro_atlas.png)
- Elite sprites: 16x16, 128 tiles, arranged in a 16x8 grid (po-x_elite_atlas.png)
- Boss sprites: 24x24, 48 tiles, arranged in a 8x6 grid (po-x_boss_atlas.png)

## Indexing
- Each sprite has a unique ID and coordinates in the atlas
- Use po-x_sprite_metadata.json for lookup

## Integration
- Load atlas PNG
- Use metadata to extract sprite tiles
- Apply animation rules per frame
- Use palette for LCD emulation

## Example
- To get ENM_001: find atlas_x=1, atlas_y=0 in po-x_micro_atlas.png
- To animate: cycle frames as per frame_rules

---

For full game integration, use the generator script to produce PNGs, then combine into atlas PNGs as described. If you need the actual PNGs or want to run the generator, use po-x_sprite_generator.py.
