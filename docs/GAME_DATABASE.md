# POX Game Database System

This system provides a simple SQL-like database for C++ to store and query game data (creatures, items, parts, etc.).

- Tables can be created with columns: id, num, name, and any other fields.
- Rows can be inserted and queried with a simple select/where interface.

## Example Usage

```cpp
#include "pox/db/database.hpp"

pox::db::Database db;
db.createTable("creatures", {
    {"id", "int"},
    {"num", "int"},
    {"name", "string"},
    {"type", "string"},
    {"hp", "int"},
    {"attack", "int"}
});

db.insert("creatures", {{
    {"id", 1},
    {"num", 101},
    {"name", "Infector"},
    {"type", "virus"},
    {"hp", 100},
    {"attack", 20}
}});

// Query by name
auto results = db.select("creatures", "name=Infector");
```

- Extend with more tables: items, parts, weapons, armor, etc.
- Integrate with other systems for dynamic game data.
