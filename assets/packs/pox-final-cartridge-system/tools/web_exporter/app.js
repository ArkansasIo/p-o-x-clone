// POX Asset Exporter (no deps)
// - Load image into canvas
// - Quantize to 4 shades (2bpp)
// - Export: raw 2bpp, tile-packed 2bpp, WAD with lumps: META + IMG2BPP + TILES2BPP
//
// 2bpp packing: 4 pixels per byte, bits [7..6][5..4][3..2][1..0] where each pixel is 0..3.

const $ = (id)=>document.getElementById(id);

const srcC = $("src");
const lcdC = $("lcd");
const sctx = srcC.getContext("2d");
const lctx = lcdC.getContext("2d");

const log = (msg)=> { $("log").textContent += msg + "\n"; $("log").scrollTop = 1e9; };
const clr = ()=> { $("log").textContent = ""; };

const LCD = [
  [15,25,15,255],
  [55,75,55,255],
  [120,150,120,255],
  [210,230,210,255],
];

function clamp(v,a,b){ return Math.max(a, Math.min(b,v)); }

function bayer2(x,y){
  // 4x4 Bayer matrix normalized to [0..1)
  const m = [
    [ 0, 8, 2,10],
    [12, 4,14, 6],
    [ 3,11, 1, 9],
    [15, 7,13, 5],
  ];
  return (m[y&3][x&3] / 16);
}

function luminance(r,g,b){
  return (0.2126*r + 0.7152*g + 0.0722*b);
}

function quantizeTo4(imgData, ditherMode){
  const d = imgData.data;
  for(let y=0; y<imgData.height; y++){
    for(let x=0; x<imgData.width; x++){
      const i = (y*imgData.width + x)*4;
      const r=d[i], g=d[i+1], b=d[i+2], a=d[i+3];
      if(a<10){ d[i]=LCD[3][0]; d[i+1]=LCD[3][1]; d[i+2]=LCD[3][2]; d[i+3]=255; continue; }
      let lum = luminance(r,g,b); // 0..255
      if(ditherMode==="bayer"){
        lum = clamp(lum + (bayer2(x,y)-0.5)*32, 0, 255);
      }
      const level = Math.round(lum / 85); // 0..3
      const c = LCD[level];
      d[i]=c[0]; d[i+1]=c[1]; d[i+2]=c[2]; d[i+3]=255;
    }
  }
  return imgData;
}

function to2bpp(imgData){
  // Map each pixel to 0..3 by nearest luminance bucket (assumes already quantized)
  const w = imgData.width, h = imgData.height;
  const d = imgData.data;
  const out = new Uint8Array(Math.ceil(w*h/4));
  let o=0, nib=0, shift=6;
  for(let y=0;y<h;y++){
    for(let x=0;x<w;x++){
      const i=(y*w+x)*4;
      const lum = luminance(d[i],d[i+1],d[i+2]); // 0..255
      const level = Math.round(lum / 85) & 3;
      nib |= (level << shift);
      if(shift===0){
        out[o++] = nib;
        nib=0;
        shift=6;
      } else {
        shift-=2;
      }
    }
  }
  if(shift!==6) out[o++] = nib;
  return out.slice(0,o);
}

function padToTile(imgData, tile){
  const w=imgData.width, h=imgData.height;
  const nw = Math.ceil(w/tile)*tile;
  const nh = Math.ceil(h/tile)*tile;
  if(nw===w && nh===h) return imgData;
  const tmp = document.createElement("canvas");
  tmp.width=nw; tmp.height=nh;
  const t = tmp.getContext("2d");
  t.fillStyle = `rgba(${LCD[3][0]},${LCD[3][1]},${LCD[3][2]},1)`;
  t.fillRect(0,0,nw,nh);
  t.putImageData(imgData,0,0);
  return t.getImageData(0,0,nw,nh);
}

function tilePack2bpp(imgData, tile, interleave=true){
  const w=imgData.width, h=imgData.height;
  const tilesX = w/tile, tilesY = h/tile;
  const bytesPerTile = (tile*tile)/4;
  const out = new Uint8Array(tilesX*tilesY*bytesPerTile);
  let o=0;
  const d = imgData.data;
  function levelAt(x,y){
    const i=(y*w+x)*4;
    const lum = luminance(d[i],d[i+1],d[i+2]);
    return (Math.round(lum/85)&3);
  }
  for(let ty=0; ty<tilesY; ty++){
    for(let tx=0; tx<tilesX; tx++){
      // pack one tile
      let nib=0, shift=6;
      for(let py=0; py<tile; py++){
        for(let px=0; px<tile; px++){
          const x = tx*tile + px;
          const y = ty*tile + py;
          const lv = levelAt(x,y);
          nib |= (lv<<shift);
          if(shift===0){ out[o++] = nib; nib=0; shift=6; }
          else shift-=2;
        }
      }
    }
  }
  return out;
}

// ---------- WAD builder ----------
function u32le(v){
  const b=new Uint8Array(4);
  b[0]=v&255; b[1]=(v>>8)&255; b[2]=(v>>16)&255; b[3]=(v>>24)&255;
  return b;
}
function concat(arrs){
  let n=0; for(const a of arrs) n+=a.length;
  const out=new Uint8Array(n);
  let o=0;
  for(const a of arrs){ out.set(a,o); o+=a.length; }
  return out;
}
function str8(s, n){
  const enc=new TextEncoder().encode(s);
  const out=new Uint8Array(n);
  out.fill(0);
  out.set(enc.slice(0,n));
  return out;
}
function buildWad(lumps){
  // WAD2: "PWAD" + dirOffset + dirCount + data... + directory
  // Directory entry: offset(u32) size(u32) name[8]
  let dataParts=[];
  let dir=[];
  let offset = 12; // header size
  for(const l of lumps){
    const payload = l.data;
    dataParts.push(payload);
    dir.push({offset, size: payload.length, name: l.name});
    offset += payload.length;
  }
  const dirOffset = offset;
  let dirBytes=[];
  for(const e of dir){
    dirBytes.push(u32le(e.offset));
    dirBytes.push(u32le(e.size));
    dirBytes.push(str8(e.name,8));
  }
  const header = concat([
    new TextEncoder().encode("PWAD"),
    u32le(dirOffset),
    u32le(dir.length),
  ]);
  return concat([header, ...dataParts, ...dirBytes]);
}

// ---------- download helpers ----------
function downloadBlob(name, bytes, mime="application/octet-stream"){
  const blob = new Blob([bytes],{type:mime});
  const url = URL.createObjectURL(blob);
  const a = document.createElement("a");
  a.href=url; a.download=name; a.click();
  setTimeout(()=>URL.revokeObjectURL(url), 1500);
}

function defaultMeta(){
  return {
    game:"POX Clone",
    target:{ lcd:"128x64", bpp:2, tile:8 },
    lumps:[
      {name:"IMG2BPP", purpose:"raw packed pixels"},
      {name:"TILES2BP", purpose:"tile-packed pixels"},
      {name:"META", purpose:"json metadata"}
    ]
  };
}

$("meta").value = JSON.stringify(defaultMeta(), null, 2);

// ---------- UI wiring ----------
let current = null; // {imgData, lcdData}
function fitCanvases(w,h){
  srcC.width=w; srcC.height=h;
  lcdC.width=w; lcdC.height=h;
}

$("file").addEventListener("change", async (ev)=>{
  const f = ev.target.files?.[0];
  if(!f) return;
  clr();
  const url = URL.createObjectURL(f);
  const img = new Image();
  img.onload = ()=>{
    fitCanvases(img.width, img.height);
    sctx.clearRect(0,0,srcC.width,srcC.height);
    sctx.drawImage(img,0,0);
    const src = sctx.getImageData(0,0,img.width,img.height);
    const lcd = quantizeTo4(new ImageData(new Uint8ClampedArray(src.data), src.width, src.height), $("dither").value);
    lctx.putImageData(lcd,0,0);
    current = {src, lcd};
    log(`Loaded ${f.name} (${img.width}x${img.height})`);
  };
  img.src=url;
});

$("dither").addEventListener("change", ()=>{
  if(!current) return;
  clr();
  const lcd = quantizeTo4(new ImageData(new Uint8ClampedArray(current.src.data), current.src.width, current.src.height), $("dither").value);
  lctx.putImageData(lcd,0,0);
  current.lcd = lcd;
  log("Updated LCD preview.");
});

$("btn2bpp").addEventListener("click", ()=>{
  if(!current) return;
  const tile = parseInt($("tileSize").value,10);
  const imgData = $("padToTile").checked ? padToTile(current.lcd, tile) : current.lcd;
  const bin = to2bpp(imgData);
  downloadBlob("image_2bpp.bin", bin);
  log(`Exported raw 2bpp: ${bin.length} bytes`);
});

$("btnTiles").addEventListener("click", ()=>{
  if(!current) return;
  const tile = parseInt($("tileSize").value,10);
  const imgData = $("padToTile").checked ? padToTile(current.lcd, tile) : current.lcd;
  const bin = tilePack2bpp(imgData, tile, $("interleave").checked);
  downloadBlob(`tiles_${tile}x${tile}_2bpp.bin`, bin);
  log(`Exported tileset: ${bin.length} bytes (${imgData.width/tile}x${imgData.height/tile} tiles)`);
});

$("btnMeta").addEventListener("click", ()=>{
  const bytes = new TextEncoder().encode($("meta").value);
  downloadBlob("metadata.json", bytes, "application/json");
  log("Downloaded metadata.json");
});

$("btnProject").addEventListener("click", ()=>{
  const proj = {
    version:1,
    rom:"roms/main.poxr",
    wad:"wad/assets.wad",
    sram:"sram/save.sram",
    notes:"Edit in the exporter and repack with pox_packer.js"
  };
  downloadBlob("pox_project.json", new TextEncoder().encode(JSON.stringify(proj,null,2)), "application/json");
  log("Downloaded pox_project.json");
});

$("btnWad").addEventListener("click", ()=>{
  if(!current) return;
  const tile = parseInt($("tileSize").value,10);
  const imgData = $("padToTile").checked ? padToTile(current.lcd, tile) : current.lcd;
  const raw = to2bpp(imgData);
  const tiles = tilePack2bpp(imgData, tile, $("interleave").checked);
  const meta = new TextEncoder().encode($("meta").value);

  const wad = buildWad([
    {name:"META", data: meta},
    {name:"IMG2BPP", data: raw},
    {name:"TILES2BP", data: tiles},
  ]);
  downloadBlob("assets.wad", wad);
  log(`Exported WAD: ${wad.length} bytes (3 lumps)`);
});
