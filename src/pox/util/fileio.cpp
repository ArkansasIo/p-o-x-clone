#include "pox/util/fileio.hpp"
#include <fstream>

namespace pox::util {

std::vector<u8> read_file(const std::string& path) {
  std::ifstream f(path, std::ios::binary);
  if (!f) return {};
  f.seekg(0, std::ios::end);
  auto n = f.tellg();
  if (n <= 0) return {};
  f.seekg(0, std::ios::beg);
  std::vector<u8> d((size_t)n);
  f.read((char*)d.data(), n);
  return d;
}

bool write_file(const std::string& path, const std::vector<u8>& data) {
  std::ofstream f(path, std::ios::binary);
  if (!f) return false;
  f.write((const char*)data.data(), (std::streamsize)data.size());
  return true;
}

} // namespace pox::util
