// Single-header nlohmann/json stub for build/test only. Replace with full version for production.
#ifndef NLOHMANN_JSON_HPP
#define NLOHMANN_JSON_HPP
#include <map>
#include <string>
#include <vector>
#include <sstream>
namespace nlohmann {
class json {
public:
    template<typename T>
    T get() const { return T{}; }
    template<typename T>
    operator T() const { return T{}; }
    template<typename T>
    json& operator[](const T&) { return *this; }
    template<typename T>
    const json& operator[](const T&) const { return *this; }
    friend std::istream& operator>>(std::istream& is, json&) { return is; }
};
}
#endif // NLOHMANN_JSON_HPP
