#include <iostream>
#include <filesystem>
#include <queue>

namespace fs = std::filesystem;

void list_folders_recursively(const fs::path& path, int indent = 0) {
    // recursively list folder names
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_directory()) {
            const auto& sub_folder = entry.path();
            std::cout << std::string(indent, ' ') << sub_folder << "\n";
            list_folders_recursively(sub_folder, indent + 2);
        }
    }
}

void list_folders(const fs::path& path) {
    std::queue<std::pair<fs::path, int>> paths;

    // list folder names
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_directory()) {
            paths.emplace(entry.path(), 0);
        }
    }

    while (!paths.empty()) {
        auto current = paths.front();
        std::cout << std::string(current.second, ' ') << current.first << "\n";
        paths.pop();

        for (const auto& entry : fs::directory_iterator(current.first)) {
            if (entry.is_directory()) {
                paths.emplace(entry.path(), current.second + 2);
            }
        }
    }
}

int main() {
    auto path = fs::path(".");

    std::cout << "Recursive..." << std::endl;
    std::cout << "------------" << std::endl;
    std::cout << std::endl;

    list_folders_recursively(path);

    std::cout << "Non-Recursive..." << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << std::endl;

    list_folders(path);

    return 0;
}
