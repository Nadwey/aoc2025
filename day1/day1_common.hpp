#ifndef AOC_2025_DAY1_COMMON_HPP
#define AOC_2025_DAY1_COMMON_HPP

#include <fstream>
#include <filesystem>
#include <vector>
#include <string>

std::filesystem::path get_souce_dir() {
    return std::filesystem::path(__FILE__).parent_path();
}

std::vector<std::string> load_moves() {
    std::ifstream input(get_souce_dir().append("input.txt"));
    if (!input.is_open()) {
        throw std::runtime_error("Could not open input.txt");
    }

    std::vector<std::string> moves;

    while (!input.eof()) {
        std::string line;
        std::getline(input, line);

        if (line.empty())
            continue;

        moves.push_back(line);
    }

    return moves;
}

#endif //AOC_2025_DAY1_COMMON_HPP
