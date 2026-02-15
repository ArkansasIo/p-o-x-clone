// POX Game Database System (SQL-like interface) implementation
#include "pox/db/database.hpp"
#include <algorithm>

namespace pox::db {

void Database::createTable(const std::string& name, const std::vector<DBColumn>& columns) {
    tables_[name] = DBTable{name, columns, {}};
}

void Database::insert(const std::string& table, const DBRow& row) {
    auto it = tables_.find(table);
    if (it != tables_.end()) {
        it->second.rows.push_back(row);
    }
}

std::vector<DBRow> Database::select(const std::string& table, const std::string& where) {
    std::vector<DBRow> result;
    auto it = tables_.find(table);
    if (it == tables_.end()) return result;
    // Simple select: if where is empty, return all
    if (where.empty()) {
        return it->second.rows;
    }
    // Very basic where: "id=42" or "name=Bob"
    size_t eq = where.find('=');
    if (eq == std::string::npos) return result;
    std::string key = where.substr(0, eq);
    std::string val = where.substr(eq+1);
    key.erase(std::remove_if(key.begin(), key.end(), ::isspace), key.end());
    val.erase(std::remove_if(val.begin(), val.end(), ::isspace), val.end());
    for (const auto& row : it->second.rows) {
        auto vit = row.values.find(key);
        if (vit != row.values.end()) {
            if (std::holds_alternative<int>(vit->second) && std::to_string(std::get<int>(vit->second)) == val)
                result.push_back(row);
            else if (std::holds_alternative<double>(vit->second) && std::to_string(std::get<double>(vit->second)) == val)
                result.push_back(row);
            else if (std::holds_alternative<std::string>(vit->second) && std::get<std::string>(vit->second) == val)
                result.push_back(row);
        }
    }
    return result;
}

std::optional<DBTable> Database::getTable(const std::string& name) const {
    auto it = tables_.find(name);
    if (it != tables_.end()) return it->second;
    return std::nullopt;
}

} // namespace pox::db
