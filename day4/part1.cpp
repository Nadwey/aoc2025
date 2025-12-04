#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <array>

std::filesystem::path get_souce_dir() {
    return std::filesystem::path(__FILE__).parent_path();
}

using RollRow = std::vector<bool>;
using RollGrid = std::vector<RollRow>;

RollGrid load_rows() {
    std::ifstream input_file(get_souce_dir().append("input.txt"));

    RollGrid grid;

    while (!input_file.eof()) {
        std::string line;
        std::getline(input_file, line);

        if (line.empty()) {
            continue;
        }

        RollRow row;
        for (const char c : line) {
            row.push_back(c == '@');
        }

        grid.push_back(row);
    }

    return grid;
}

constexpr bool in_grid(const RollGrid& grid, const int x, const int y) {
    return !(x < 0 || y < 0 || x >= grid[0].size() || y >= grid.size());
}

constexpr int get_value_for(const RollGrid& grid, const int x, const int y) {
    return in_grid(grid, x, y) && grid[y][x];
}

/**
 * x and y is the center of the 1x3 column
 */
constexpr int get_column(const RollGrid& grid, const int x, const int y) {
    return get_value_for(grid, x, y - 1) + get_value_for(grid, x, y) + get_value_for(grid, x, y + 1);
}

int count_accessible_positions() {
    RollGrid grid = load_rows();

    int accessible = 0;

    for (int y = 0; y < grid.size(); y++) {
        const auto& row = grid[y];

        int current_rolls = get_column(grid, 0, y);


        for (int x = 0; x < row.size(); x++) {
            current_rolls += get_column(grid, x + 1, y);
            current_rolls -= get_column(grid, x - 2, y);

            if (row[x] && current_rolls - 1 < 4) {
                accessible++;
            }
        }
    }

    return accessible;
}

int main() {
    std::cout << "accessible: " << count_accessible_positions();

    return 0;
}
