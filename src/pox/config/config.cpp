// Game configuration system implementation
#include "pox/config/config.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

namespace pox {

Config& Config::instance() {
    static Config inst;
    return inst;
}

Config::Config() {}

bool Config::load(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) return false;
    values_.clear();
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key, type, value;
        if (!(iss >> key >> type >> value)) continue;
        if (type == "int") values_[key] = std::stoi(value);
        else if (type == "float") values_[key] = std::stof(value);
        else if (type == "bool") values_[key] = (value == "true");
        else values_[key] = value;
    }
    return true;
}

bool Config::save(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file) return false;
    for (const auto& [key, val] : values_) {
        file << key << " ";
        if (std::holds_alternative<int>(val)) file << "int " << std::get<int>(val);
        else if (std::holds_alternative<float>(val)) file << "float " << std::get<float>(val);
        else if (std::holds_alternative<bool>(val)) file << "bool " << (std::get<bool>(val) ? "true" : "false");
        else file << "string " << std::get<std::string>(val);
        file << "\n";
    }
    return true;
}

void Config::set(const std::string& key, const ConfigValue& value) {
    values_[key] = value;
}

std::optional<ConfigValue> Config::get(const std::string& key) const {
    auto it = values_.find(key);
    if (it != values_.end()) return it->second;
    return std::nullopt;
}

void Config::reset() {
    values_.clear();
}

} // namespace pox
