// main.cpp
#include "pox1_loader.hpp"
#include "sprite_decoder.hpp"
#include <iostream>
#include <fstream>
#include <vector>


// ...existing includes...
#include <map>
#include <random>
#include <chrono>

struct Entity {
    std::string id;
    std::string type;
    int hp;
    int atk;
    int def;
    int x, y;
    uint8_t sprite_frame;
};

std::map<std::string, Entity> create_entities() {
    std::map<std::string, Entity> entities;
    entities["player"] = {"PLY_000", "player", 100, 12, 8, 4, 4, 0};
    entities["enemy"] = {"ENM_001", "enemy", 40, 8, 4, 6, 4, 0};
    entities["boss"] = {"BOS_000", "boss", 200, 20, 12, 8, 4, 0};
    entities["elite"] = {"ELT_000", "elite", 80, 14, 10, 2, 6, 0};
    entities["object"] = {"OBJ_000", "object", 0, 0, 0, 5, 2, 0};
    entities["item"] = {"ITM_000", "item", 0, 0, 0, 3, 7, 0};
    entities["effect"] = {"FX_000", "effect", 0, 0, 0, 7, 7, 0};
    return entities;
}

void print_entity(const Entity& e) {
    std::cout << e.type << " (" << e.id << ") HP:" << e.hp << " ATK:" << e.atk << " DEF:" << e.def << " Pos:(" << e.x << "," << e.y << ")\n";
}

void handle_input(Entity& player, char input) {
    switch (input) {
        case 'w': player.y = std::max(0, player.y - 1); break;
        case 's': player.y = std::min(7, player.y + 1); break;
        case 'a': player.x = std::max(0, player.x - 1); break;
        case 'd': player.x = std::min(7, player.x + 1); break;
        case 'f': player.sprite_frame = (player.sprite_frame + 1) % 2; break;
    }
}

void game_tick(std::map<std::string, Entity>& entities) {
    Entity& player = entities["player"];
    Entity& enemy = entities["enemy"];
    Entity& elite = entities["elite"];
    Entity& boss = entities["boss"];
    // Enemy AI: move toward player
    if (enemy.x < player.x) enemy.x++;
    else if (enemy.x > player.x) enemy.x--;
    if (enemy.y < player.y) enemy.y++;
    else if (enemy.y > player.y) enemy.y--;
    // Elite AI: random move
    elite.x = std::max(0, std::min(7, elite.x + (rand()%3 - 1)));
    elite.y = std::max(0, std::min(7, elite.y + (rand()%3 - 1)));
    // Boss AI: move horizontally
    boss.x = (boss.x + 1) % 8;
    // Combat: enemy attacks player if adjacent
    if (std::abs(enemy.x - player.x) + std::abs(enemy.y - player.y) == 1) {
        int dmg = std::max(0, enemy.atk - player.def);
        player.hp -= dmg;
        std::cout << "Enemy attacks player for " << dmg << " damage!\n";
    }
    // Elite attacks player if adjacent
    if (std::abs(elite.x - player.x) + std::abs(elite.y - player.y) == 1) {
        int dmg = std::max(0, elite.atk - player.def);
        player.hp -= dmg;
        std::cout << "Elite attacks player for " << dmg << " damage!\n";
    }
    // Boss attacks player if adjacent
    if (std::abs(boss.x - player.x) + std::abs(boss.y - player.y) == 1) {
        int dmg = std::max(0, boss.atk - player.def);
        player.hp -= dmg;
        std::cout << "Boss attacks player for " << dmg << " damage!\n";
    }
    // Item pickup
    Entity& item = entities["item"];
    if (player.x == item.x && player.y == item.y) {
        player.hp += 10;
        std::cout << "Player picked up item and healed 10 HP!\n";
        item.x = -1; item.y = -1;
    }
    // Effect: show effect if player at effect location
    Entity& effect = entities["effect"];
    if (player.x == effect.x && player.y == effect.y) {
        std::cout << "Player triggered effect!\n";
    }
}

void render_game(const std::map<std::string, Entity>& entities) {
    // Render grid and entities
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            bool printed = false;
            for (const auto& kv : entities) {
                const Entity& e = kv.second;
                if (e.x == x && e.y == y) {
                    std::cout << (e.type == "player" ? "P" : e.type == "enemy" ? "E" : "B");
                    printed = true;
                }
            }
            if (!printed) std::cout << ".";
        }
        std::cout << "\n";
    }
    for (const auto& kv : entities) print_entity(kv.second);
}

int main(int argc, char** argv) {

    // Save/load system
    #include <fstream>
    void save_game(const std::map<std::string, Entity>& entities) {
        std::ofstream f("pox_save.dat", std::ios::binary);
        for (const auto& kv : entities) {
            const Entity& e = kv.second;
            f.write(reinterpret_cast<const char*>(&e.hp), sizeof(e.hp));
            f.write(reinterpret_cast<const char*>(&e.x), sizeof(e.x));
            f.write(reinterpret_cast<const char*>(&e.y), sizeof(e.y));
        }
        f.close();
        std::cout << "Game saved.\n";
    }

    void load_game(std::map<std::string, Entity>& entities) {
        std::ifstream f("pox_save.dat", std::ios::binary);
        for (auto& kv : entities) {
            Entity& e = kv.second;
            f.read(reinterpret_cast<char*>(&e.hp), sizeof(e.hp));
            f.read(reinterpret_cast<char*>(&e.x), sizeof(e.x));
            f.read(reinterpret_cast<char*>(&e.y), sizeof(e.y));
        }
        f.close();
        std::cout << "Game loaded.\n";
    }

    int main(int argc, char** argv) {
        if (argc < 3) {
            std::cout << "Usage: pox_sprite_loader <pox1_index> <sprite_bin> [sprite_id]" << std::endl;
            return 1;
        }
        auto index = load_pox1_index(argv[1]);
        std::ifstream bin(argv[2], std::ios::binary);
        if (!bin) {
            std::cout << "Failed to open sprite bin." << std::endl;
            return 1;
        }
        std::string sprite_id = argc > 3 ? argv[3] : index.front().id;
        auto it = std::find_if(index.begin(), index.end(), [&](const SpriteIndexEntry& e) { return e.id == sprite_id; });
        if (it == index.end()) {
            std::cout << "Sprite ID not found." << std::endl;
            return 1;
        }
        bin.seekg(it->offset);
        std::vector<uint8_t> data(it->size);
        bin.read(reinterpret_cast<char*>(data.data()), it->size);
        auto fb = decode_sprite(data.data(), it->width, it->height, it->bpp);
        std::cout << "Sprite " << it->id << " (" << it->width << "x" << it->height << ", " << int(it->bpp) << "bpp):\n";
        for (uint16_t y = 0; y < it->height; ++y) {
            for (uint16_t x = 0; x < it->width; ++x) {
                std::cout << ((fb[y * it->width + x] & 0xFFFFFF) ? "#" : ".");
            }
            std::cout << "\n";
        }
        // Animation demo: if sprite has multiple frames, show each frame
        if (it->frames > 1) {
            std::cout << "\nAnimation frames:\n";
            for (uint8_t f = 0; f < it->frames; ++f) {
                std::cout << "Frame " << int(f) << ":\n";
                // Assume each frame is contiguous in data
                auto fb_frame = decode_sprite(data.data() + f * (it->size / it->frames), it->width, it->height, it->bpp);
                for (uint16_t y = 0; y < it->height; ++y) {
                    for (uint16_t x = 0; x < it->width; ++x) {
                        std::cout << ((fb_frame[y * it->width + x] & 0xFFFFFF) ? "#" : ".");
                    }
                    std::cout << "\n";
                }
            }
        }

        // Game loop demo
        auto entities = create_entities();
        bool running = true;
        std::cout << "\n--- PO-X CLI Game Demo ---\n";
        while (running) {
            render_game(entities);
            std::cout << "Enter command (w/a/s/d = move, f = frame, q = quit, v = save, l = load): ";
            char input;
            std::cin >> input;
            if (input == 'q') break;
            if (input == 'v') save_game(entities);
            if (input == 'l') load_game(entities);
            handle_input(entities["player"], input);
            game_tick(entities);
            if (entities["player"].hp <= 0) {
                std::cout << "Player defeated!\n";
                running = false;
            }
        }
        std::cout << "Game over.\n";
        return 0;
    }
