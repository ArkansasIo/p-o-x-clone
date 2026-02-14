// save_builder.js (Node.js, no deps)
// Builds an SRAM image with N creature slots (20-byte POX record), each with CRC16/IBM.
// Output is a raw SRAM blob, typically mapped to 0x9800 in the emulator.
//
// Record layout (20 bytes):
// 0 head_id,1 head_hp,2 body_id,3 body_hp,4 tail_id,5 tail_hp,
// 6..11 wad_char_index[6], 12..17 wad_name_index[6],
// 18..19 crc16 little endian over bytes 0..17.

const fs = require("fs");
const path = require("path");

function crc16_ibm(buf){
  let crc = 0xFFFF;
  for (let i=0;i<18;i++){
    crc ^= buf[i];
    for(let b=0;b<8;b++){
      const lsb = crc & 1;
      crc >>>= 1;
      if(lsb) crc ^= 0xA001;
    }
  }
  return crc & 0xFFFF;
}

function write(outPath, slots=8){
  const slotSize = 20;
  const sram = Buffer.alloc(slots*slotSize, 0);

  for(let s=0;s<slots;s++){
    const off = s*slotSize;
    // defaults vary per slot
    sram[off+0] = 0x40 + (s&7);
    sram[off+1] = 30;
    sram[off+2] = 0x4F + (s&7);
    sram[off+3] = 30;
    sram[off+4] = 0x6F + (s&7);
    sram[off+5] = 30;
    for(let i=0;i<6;i++) sram[off+6+i] = i;
    // name = "POX   " using A-Z mapping: P=16,O=15,X=24
    const name = [16,15,24,0,0,0];
    for(let i=0;i<6;i++) sram[off+12+i] = name[i];
    const crc = crc16_ibm(sram.subarray(off, off+20));
    sram[off+18] = crc & 0xFF;
    sram[off+19] = (crc>>8) & 0xFF;
  }

  fs.mkdirSync(path.dirname(outPath), {recursive:true});
  fs.writeFileSync(outPath, sram);
  console.log(`SRAM written: ${outPath} (${slots} slots)`);
}

if(require.main===module){
  const out = process.argv[2] || "sram/save.sram";
  const slots = parseInt(process.argv[3] || "8",10);
  write(out, slots);
}
