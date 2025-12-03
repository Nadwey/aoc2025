#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <array>

constexpr int BANK_SIZE = 100;

using BankArray = std::array<int, BANK_SIZE>;

std::filesystem::path get_souce_dir() {
    return std::filesystem::path(__FILE__).parent_path();
}

template<typename T = unsigned char>
std::vector<BankArray> load_banks() {
    std::ifstream input_file(get_souce_dir().append("input.txt"));

    std::vector<BankArray> out;

    while (!input_file.eof()) {
        std::string line;
        std::getline(input_file, line);

        if (line.empty()) {
            continue;
        }

        if (line.size() != BANK_SIZE) {
            throw std::runtime_error("fix yo BANK_SIZE");
        }

        BankArray bank{};
        for (int i = 0; i < BANK_SIZE; i++) {
            bank[i] = line[i] - 48;
        }

        out.push_back(bank);
    }

    return out;
}

/**
 * @return index
 */
int find_largest(const BankArray& bank, int start_index = 0, const int end_index = BANK_SIZE) {
    int largest_index = 0;
    int largest = 0;

    for (int i = start_index; i < end_index; i++) {
        int current = bank[i];
        if (current > largest) {
            largest = current;
            largest_index = i;
        }
    }

    return largest_index;
}

uint64_t get_max_joltage(const BankArray& bank) {
    uint64_t max_joltage = 0;

    int prev_highest_index = -1;
    for (int digit = 0; digit < 12; digit++) {
        int highest_index = find_largest(bank, prev_highest_index + 1, BANK_SIZE + digit - 11);

        max_joltage *= 10;
        max_joltage += bank[highest_index];
        prev_highest_index = highest_index;
    }

    return max_joltage;
};

int main() {
    uint64_t sum = 0;
    for (BankArray& bank : load_banks()) {
        uint64_t max_joltage = get_max_joltage(bank);
        std::cout << "max for bank: " << max_joltage << "\n";
        sum += max_joltage;
    }
    std::cout << "max: " << sum;

    return 0;
}
