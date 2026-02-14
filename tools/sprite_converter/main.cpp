#include <cstdio>
#include <vector>
#include <string>
#include <fstream>

// Stub converter: converts a raw grayscale PGM (P5) into 2bpp packed bytes.
// This matches the placeholder display pipeline (4 pixels per byte).
// Replace with real PO-X tile/bitplane format once known.

static bool read_file(const std::string& path, std::vector<unsigned char>& out) {
  std::ifstream f(path, std::ios::binary);
  if (!f) return false;
  f.seekg(0, std::ios::end);
  auto n = f.tellg();
  if (n <= 0) return false;
  f.seekg(0, std::ios::beg);
  out.resize((size_t)n);
  f.read((char*)out.data(), n);
  return true;
}

static bool write_file(const std::string& path, const std::vector<unsigned char>& data) {
  std::ofstream f(path, std::ios::binary);
  if (!f) return false;
  f.write((const char*)data.data(), (std::streamsize)data.size());
  return true;
}

int main(int argc, char** argv) {
  if (argc < 5) {
    std::printf("Usage: pox_sprite_converter <in.pgm(P5)> <w> <h> <out.bin>\n");
    std::printf("Note: This is a STUB for the placeholder 2bpp VRAM format.\n");
    return 1;
  }

  const std::string in = argv[1];
  const int w = std::atoi(argv[2]);
  const int h = std::atoi(argv[3]);
  const std::string outp = argv[4];

  std::vector<unsigned char> d;
  if (!read_file(in, d)) {
    std::printf("Failed to read %s\n", in.c_str());
    return 1;
  }

  // Very minimal PGM parse (expects header 'P5', then width height, then maxval, then raw bytes)
  // For real usage, replace with a robust parser.
  size_t i = 0;
  auto skip_ws = [&]() {
    while (i < d.size() && (d[i]==' '||d[i]=='\n'||d[i]=='\r'||d[i]=='\t')) i++;
  };
  auto read_token = [&]() -> std::string {
    skip_ws();
    std::string t;
    while (i < d.size() && !(d[i]==' '||d[i]=='\n'||d[i]=='\r'||d[i]=='\t')) {
      t.push_back((char)d[i++]);
    }
    return t;
  };

  const std::string magic = read_token();
  if (magic != "P5") {
    std::printf("Only P5 PGM supported in stub.\n");
    return 1;
  }
  const int fw = std::stoi(read_token());
  const int fh = std::stoi(read_token());
  const int maxv = std::stoi(read_token());
  (void)maxv;
  if (fw != w || fh != h) {
    std::printf("Header w/h mismatch: header=%dx%d args=%dx%d\n", fw, fh, w, h);
    return 1;
  }
  // consume one whitespace
  if (i < d.size() && (d[i]=='\n' || d[i]=='\r' || d[i]==' ' || d[i]=='\t')) i++;
  const size_t pix_off = i;
  const size_t pix_n = (size_t)w * (size_t)h;
  if (pix_off + pix_n > d.size()) {
    std::printf("PGM truncated.\n");
    return 1;
  }

  std::vector<unsigned char> out;
  out.reserve((pix_n + 3) / 4);

  auto to_2bpp = [&](unsigned char g)->unsigned char{
    // map 0..255 to 0..3
    return (unsigned char)((g * 3) / 255);
  };

  for (size_t p = 0; p < pix_n; ) {
    unsigned char b = 0;
    for (int k = 0; k < 4; k++) {
      unsigned char idx = 0;
      if (p < pix_n) idx = to_2bpp(d[pix_off + p]);
      const int shift = 6 - 2*k;
      b |= (unsigned char)((idx & 0x3) << shift);
      p++;
    }
    out.push_back(b);
  }

  if (!write_file(outp, out)) {
    std::printf("Failed to write %s\n", outp.c_str());
    return 1;
  }

  std::printf("Wrote %s (%zu bytes)\n", outp.c_str(), out.size());
  return 0;
}
