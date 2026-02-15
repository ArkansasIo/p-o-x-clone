#include "combat.hpp"
#include <random>
#include <sstream>

CombatResult simulateCombat(const PlayerInfo& attacker, const PlayerInfo& defender, const WorldZone& zone) {
    // Simple deterministic combat simulation for async/offline
    std::mt19937 rng(attacker.id ^ defender.id ^ static_cast<uint32_t>(zone.planetSeed));
    int attackerPower = 50 + (rng() % 50); // Example: 50-99
    int defenderPower = 50 + (rng() % 50);
    bool attackerWin = attackerPower > defenderPower;
    int resourcesStolen = attackerWin ? (rng() % 100) : 0;
    std::ostringstream log;
    log << "Attacker: " << attacker.name << " (Power: " << attackerPower << ")\n";
    log << "Defender: " << defender.name << " (Power: " << defenderPower << ")\n";
    log << (attackerWin ? "Attacker wins!" : "Defender holds!") << "\n";
    if (attackerWin) log << "Resources stolen: " << resourcesStolen << "\n";
    return {attackerWin, resourcesStolen, log.str()};
}
