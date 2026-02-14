// pox_packer.js (Node.js, no deps)
// Creates a POXC "cartridge" container that bundles: ROM (.poxr or raw), WAD, SRAM image, and metadata.
// Layout:
// 0x00  'POXC' (4)
// 0x04  u32 version = 1
// 0x08  u32 romOffset
// 0x0C  u32 romSize
// 0x10  u32 wadOffset
// 0x14  u32 wadSize
// 0x18  u32 sramOffset
// 0x1C  u32 sramSize
// 0x20  u32 metaOffset
// 0x24  u32 metaSize
// 0x28  u32 crc32(payload from 0x00..end, crc field treated as 0)
// 0x2C  reserved (u32) = 0
// 0x30  payload blobs packed back-to-back

const fs = require("fs");

function u32le(v){
  const b = Buffer.alloc(4);
  b.writeUInt32LE(v>>>0,0);
  return b;
}

function crc32(buf){
  // classic CRC-32 (IEEE)
  let c = 0xFFFFFFFF;
  for (let i=0;i<buf.length;i++){
    c ^= buf[i];
    for(let k=0;k<8;k++){
      const m = -(c & 1);
      c = (c >>> 1) ^ (0xEDB88320 & m);
    }
  }
  return (c ^ 0xFFFFFFFF) >>> 0;
}

function read(path){ return fs.readFileSync(path); }
function write(path, buf){ fs.mkdirSync(require("path").dirname(path), {recursive:true}); fs.writeFileSync(path, buf); }

function pack({romPath, wadPath, sramPath, metaPath, outPath}){
  const rom = read(romPath);
  const wad = read(wadPath);
  const sram = read(sramPath);
  const meta = read(metaPath);

  const headerSize = 0x30;
  let off = headerSize;
  const romOffset = off; off += rom.length;
  const wadOffset = off; off += wad.length;
  const sramOffset = off; off += sram.length;
  const metaOffset = off; off += meta.length;

  const totalSize = off;
  const out = Buffer.alloc(totalSize);

  out.write("POXC", 0, "ascii");
  u32le(1).copy(out, 0x04);

  u32le(romOffset).copy(out, 0x08);
  u32le(rom.length).copy(out, 0x0C);
  u32le(wadOffset).copy(out, 0x10);
  u32le(wad.length).copy(out, 0x14);
  u32le(sramOffset).copy(out, 0x18);
  u32le(sram.length).copy(out, 0x1C);
  u32le(metaOffset).copy(out, 0x20);
  u32le(meta.length).copy(out, 0x24);

  u32le(0).copy(out, 0x28); // placeholder CRC
  u32le(0).copy(out, 0x2C);

  rom.copy(out, romOffset);
  wad.copy(out, wadOffset);
  sram.copy(out, sramOffset);
  meta.copy(out, metaOffset);

  const crc = crc32(out);
  u32le(crc).copy(out, 0x28);

  write(outPath, out);
  console.log(`POXC written: ${outPath}`);
  console.log(` rom ${rom.length} bytes, wad ${wad.length}, sram ${sram.length}, meta ${meta.length}`);
  console.log(` crc32=0x${crc.toString(16).padStart(8,"0")}`);
}

function usage(){
  console.log("Usage:");
  console.log("  node tools/node/pox_packer.js pack --rom roms/main.poxr --wad wad/assets.wad --sram sram/save.sram --meta metadata.json --out cartridge.poxc");
}

if (require.main === module){
  const args = process.argv.slice(2);
  const cmd = args[0];
  if (cmd !== "pack") return usage();
  const opt = {};
  for(let i=1;i<args.length;i+=2){
    opt[args[i].replace(/^--/,"")] = args[i+1];
  }
  if(!opt.rom || !opt.wad || !opt.sram || !opt.meta || !opt.out) return usage();
  pack({romPath: opt.rom, wadPath: opt.wad, sramPath: opt.sram, metaPath: opt.meta, outPath: opt.out});
}
