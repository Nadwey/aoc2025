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

        // part 2
        int full_rotations = abs(relative_dial_move) / 100;

        // if it lands on zero, it will be counted later
        if (dial_pos != 0) {
            int tricky_part = relative_dial_move % 100;
            int absolute_pos = direction == 1 ? (100 - dial_pos) : dial_pos;

            if (absolute_pos - abs(tricky_part) < 0) {
                zero_count++;
            }
        }

        zero_count += full_rotations;

        dial_pos += relative_dial_move;
        dial_pos = dial_pos % 100;
        if (dial_pos < 0) {
            dial_pos = 100 - abs(dial_pos);
        }

        if (dial_pos == 0) {
            zero_count++;
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
