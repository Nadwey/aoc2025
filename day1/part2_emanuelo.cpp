// look at part2 for a better solution

#include "day1_common.hpp"
#include <iostream>
#include <vector>

int count_zeros(std::vector<std::string>& str_moves) {
    int dial_pos = 50;
    int zero_count = 0;

    for (std::string& str_move : str_moves) {
        int direction = str_move[0] == 'R' ? 1 : -1;
        int steps = std::atoi(str_move.c_str() + 1);

        int relative_dial_move = steps * direction;

        for (int i = 0; i < abs(relative_dial_move); i++) {
            dial_pos += direction;
            dial_pos = dial_pos % 100;

            if (dial_pos == 0) {
                zero_count++;
            }
        }
    }

    return zero_count;
}

int main() {
    std::vector<std::string> moves = load_moves();

    std::cout << "landed on/passed through zero: " << count_zeros(moves)
              << std::endl;

    return 0;
}
