// sfx_synth.js (Node.js, no deps)
// Generates simple retro wave SFX as WAV (PCM16).
// Types: square, triangle, noise.
// Usage: node tools/node/sfx_synth.js square 880 0.2 out.wav

const fs = require("fs");
const path = require("path");

function wavHeader(sampleRate, samples){
  const byteRate = sampleRate * 2;
  const dataBytes = samples * 2;
  const riffSize = 36 + dataBytes;
  const b = Buffer.alloc(44);
  b.write("RIFF",0); b.writeUInt32LE(riffSize,4); b.write("WAVE",8);
  b.write("fmt ",12); b.writeUInt32LE(16,16);
  b.writeUInt16LE(1,20); b.writeUInt16LE(1,22);
  b.writeUInt32LE(sampleRate,24); b.writeUInt32LE(byteRate,28);
  b.writeUInt16LE(2,32); b.writeUInt16LE(16,34);
  b.write("data",36); b.writeUInt32LE(dataBytes,40);
  return b;
}

function gen(type, freq, seconds, sampleRate=22050){
  const n = Math.max(1, Math.floor(seconds*sampleRate));
  const out = Buffer.alloc(n*2);
  let phase = 0;
  for(let i=0;i<n;i++){
    let s = 0;
    if(type==="square"){
      phase += freq/sampleRate;
      phase -= Math.floor(phase);
      s = phase < 0.5 ? 0.8 : -0.8;
    } else if(type==="triangle"){
      phase += freq/sampleRate;
      phase -= Math.floor(phase);
      s = 2*Math.abs(2*phase-1)-1;
      s *= 0.8;
    } else if(type==="noise"){
      s = (Math.random()*2-1)*0.6;
    }
    // simple fade out
    const t = 1 - (i/(n-1));
    s *= t;
    const v = Math.max(-1, Math.min(1, s));
    out.writeInt16LE(Math.floor(v*32767), i*2);
  }
  return {sampleRate, pcm: out, samples: n};
}

function writeWav(outPath, wav){
  const hdr = wavHeader(wav.sampleRate, wav.samples);
  fs.mkdirSync(path.dirname(outPath), {recursive:true});
  fs.writeFileSync(outPath, Buffer.concat([hdr, wav.pcm]));
  console.log(`WAV written: ${outPath}`);
}

if(require.main===module){
  const type = process.argv[2] || "square";
  const freq = parseFloat(process.argv[3] || "880");
  const sec = parseFloat(process.argv[4] || "0.2");
  const out = process.argv[5] || "assets/sfx.wav";
  writeWav(out, gen(type,freq,sec));
}
