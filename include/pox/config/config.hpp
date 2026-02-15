// Game configuration system header
#pragma once
#include <string>
#include <map>
#include <variant>
#include <optional>

namespace pox {

using ConfigValue = std::variant<int, float, bool, std::string>;

class Config {
public:
    static Config& instance();
    bool load(const std::string& filename);
    bool save(const std::string& filename) const;
    void set(const std::string& key, const ConfigValue& value);
    std::optional<ConfigValue> get(const std::string& key) const;
    void reset();
private:
    Config();
    std::map<std::string, ConfigValue> values_;
};

} // namespace pox
