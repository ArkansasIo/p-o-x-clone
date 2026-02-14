#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> files = {
        "docs/biome_data_table.csv",
        "docs/zone_data_table.csv",
        "docs/counter_data_table.csv",
        "docs/condition_data_table.csv",
        "docs/interaction_data_table.csv"
    };
    for (const auto& file : files) {
        std::ifstream f(file);
        if (!f.is_open()) {
            std::printf("Failed to open %s\n", file.c_str());
            return 1;
        }
        std::string line;
        int count = 0;
        while (std::getline(f, line)) {
            if (!line.empty()) ++count;
        }
        std::printf("%s: %d lines\n", file.c_str(), count);
        f.close();
    }
    return 0;
}
