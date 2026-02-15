# Configuration System

The configuration system provides a unified way to manage settings for the game and all subsystems (audio, video, controls, network, etc.).

- Configurations are stored in plain text files (see `config/game.cfg`).
- Each line: `key type value` (e.g., `fullscreen bool true`)
- Supported types: int, float, bool, string
- The config system is accessible via the `pox::Config` singleton.

## Usage

**C++ Example:**

```cpp
#include "pox/config/config.hpp"

// Set a value
pox::Config::instance().set("fullscreen", true);

// Get a value
if (auto val = pox::Config::instance().get("fullscreen")) {
    if (std::holds_alternative<bool>(*val)) {
        bool fullscreen = std::get<bool>(*val);
        // ...
    }
}

// Load from file
pox::Config::instance().load("config/game.cfg");

// Save to file
pox::Config::instance().save("config/game.cfg");
```

## Extending
- Add new keys/types as needed for subsystems (audio, video, controls, etc.).
- Use `pox::Config` in any system to read/write settings.
