#include "patch_system.hpp"
#include "patch_utils.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// Simulate applying a binary patch to a file
void apply_patch(const std::string& targetFile, const std::string& patchFile) {
    std::cout << "[Patch] Applying patch: " << patchFile << " to " << targetFile << std::endl;
    std::ifstream patch(patchFile, std::ios::binary);
    if (!patch) {
        std::cerr << "[Patch] Failed to open patch file!" << std::endl;
        return;
    }
    std::ofstream target(targetFile, std::ios::binary | std::ios::app);
    if (!target) {
        std::cerr << "[Patch] Failed to open target file!" << std::endl;
        return;
    }
    std::vector<char> buffer((std::istreambuf_iterator<char>(patch)), std::istreambuf_iterator<char>());
    target.write(buffer.data(), buffer.size());
    std::cout << "[Patch] Patch applied successfully." << std::endl;
    verify_patch(targetFile);
}
