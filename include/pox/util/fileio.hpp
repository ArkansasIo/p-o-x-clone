#pragma once
#include <string>
#include <vector>
#include "pox/types.hpp"

namespace pox::util {
  std::vector<u8> read_file(const std::string& path);
  bool write_file(const std::string& path, const std::vector<u8>& data);
}
