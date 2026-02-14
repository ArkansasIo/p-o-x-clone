// wad_builder.js (Node.js, no deps)
// Builds a minimal PWAD archive from a folder.
// Each file becomes a lump named from filename (uppercased, max 8 chars, non A-Z0-9->_ becomes _).
//
// PWAD header: 'PWAD' + dirOffset(u32) + dirCount(u32)
// Directory entry: offset(u32) size(u32) name[8]
const fs = require("fs");
const path = require("path");

function u32le(v){ const b=Buffer.alloc(4); b.writeUInt32LE(v>>>0,0); return b; }

function lumpName(p){
  const base = path.basename(p).toUpperCase().replace(/\.[^.]+$/,"");
  return base.replace(/[^A-Z0-9]/g,"_").slice(0,8).padEnd(8, "\0");
}

function build(inDir, outFile){
  const files = fs.readdirSync(inDir).filter(f=>fs.statSync(path.join(inDir,f)).isFile());
  const payloads = files.map(f=>({file:f, data: fs.readFileSync(path.join(inDir,f)), name: lumpName(f)}));

  let off = 12;
  const dir = [];
  const parts = [];
  for(const p of payloads){
    parts.push(p.data);
    dir.push({offset: off, size: p.data.length, name: p.name});
    off += p.data.length;
  }
  const dirOffset = off;
  const dirBytes = Buffer.alloc(dir.length * 16);
  for(let i=0;i<dir.length;i++){
    const e=dir[i];
    u32le(e.offset).copy(dirBytes, i*16+0);
    u32le(e.size).copy(dirBytes, i*16+4);
    Buffer.from(e.name, "binary").copy(dirBytes, i*16+8);
  }
  const header = Buffer.concat([Buffer.from("PWAD"), u32le(dirOffset), u32le(dir.length)]);
  const out = Buffer.concat([header, ...parts, dirBytes]);
  fs.mkdirSync(path.dirname(outFile), {recursive:true});
  fs.writeFileSync(outFile, out);
  console.log(`WAD written: ${outFile} (${dir.length} lumps)`);
}

if(require.main===module){
  const inDir = process.argv[2];
  const outFile = process.argv[3];
  if(!inDir || !outFile){
    console.log("Usage: node tools/node/wad_builder.js <input_folder> <out.wad>");
    process.exit(1);
  }
  build(inDir, outFile);
}
