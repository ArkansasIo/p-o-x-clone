// POX Game Database System (SQL-like interface)
#pragma once
#include <string>
#include <vector>
#include <map>
#include <variant>
#include <optional>

namespace pox::db {

using DBValue = std::variant<int, double, std::string>;

struct DBColumn {
    std::string name;
    std::string type; // "int", "double", "string"
};

struct DBRow {
    std::map<std::string, DBValue> values;
};

struct DBTable {
    std::string name;
    std::vector<DBColumn> columns;
    std::vector<DBRow> rows;
};

class Database {
public:
    void createTable(const std::string& name, const std::vector<DBColumn>& columns);
    void insert(const std::string& table, const DBRow& row);
    std::vector<DBRow> select(const std::string& table, const std::string& where = "");
    std::optional<DBTable> getTable(const std::string& name) const;
private:
    std::map<std::string, DBTable> tables_;
};

} // namespace pox::db
