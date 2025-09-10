#include <iostream>
#include <string_view>
#include <vector>

int main(const int argc, char** argv, char** envp) {
    const std::vector<std::string_view> args(argv + 1, argv + argc);
    for (const auto& arg : args) {
        std::cout << arg << std::endl;
    }

    return 0;
}
