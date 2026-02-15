# PO-X 999 Sprite Pack

This pack contains:
- 999 micro-sprites (8x8) for enemies, bosses, players, objects, items, effects, and UI
- Modular generation logic and templates
- Animation rules
- ROM atlas indexing and memory layout
- Expansion packs for 16x16 elites, 24x24 bosses, animation frames, and 1-bit LCD variants
- Naming and ID standards, variant system, and integration pipeline

## Sprite Categories
- Enemies: ENM_000–ENM_399
- Bosses: BOS_400–BOS_479
- Elites: ELT_480–ELT_607
- Players: PLY_608–PLY_667
- Objects: OBJ_668–OBJ_787
- Items: ITM_788–ITM_927
- Effects: FX_928–FX_967
- UI: UI_968–UI_998

## Atlas Structure
- 8x8 micro-sprites: assets/sprites/atlas/po-x_micro_atlas.png
- 16x16 elites: assets/sprites/atlas/po-x_elite_atlas.png
- 24x24 bosses: assets/sprites/atlas/po-x_boss_atlas.png
- Metadata: assets/sprites/atlas/po-x_sprite_metadata.json

## Animation Rules
- Idle: 2 frames
- Move: 2–4 frames
- Attack: 2 frames
- Hit: 1 frame
- Death: 3 frames

## LCD Palette (2-bit)
- 00: transparent
- 01: light
- 10: medium
- 11: dark

## Memory Layout
- 0x0000: UI
- 0x0200: Player
- 0x0600: Enemies
- 0x1400: Elites
- 0x2400: Bosses
- 0x4000: Effects

## Naming Standard
- ENM_###: standard enemy
- ELT_###: elite enemy
- BOS_###: boss
- PLY_###: player
- OBJ_###: environment
- FX_###: effects
- UI_###: interface

## Variant System
- Armored, corrupted, energized, infected, quantum

## Expansion
- Elite & Boss atlas pack
- Animated sprite sheet set
- 1-bit LCD true hardware pack
- Player characters & suit upgrades
- Environment tiles & map icons
- Procedural sprite generator GUI
- PO-X ROM integration toolkit
- PO-X enemy encyclopedia

---

For full integration, use the provided atlas PNGs, metadata JSON, and follow the naming/indexing rules. If you need the actual PNGs, generator scripts, or further expansion, request the specific asset or code.
