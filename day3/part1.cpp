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
int find_largest(const BankArray& bank, const int skip_index = -1, int start_index = 0) {
    int largest_index = 0;
    int largest = 0;

    for (int i = start_index; i < BANK_SIZE; i++) {
        if (i == skip_index) {
            continue;
        }

        int current = bank[i];
        if (current > largest) {
            largest = current;
            largest_index = i;
        }
    }

    return largest_index;
}

int get_max_joltage(const BankArray& bank) {
    int high_index = find_largest(bank);
    int low_index = find_largest(bank, high_index);

    bool swapped = false;
    if (high_index > low_index && bank[high_index] > bank[low_index]) {
        std::swap(high_index, low_index);
        swapped = true;
    }

    if (high_index < low_index && swapped && low_index != BANK_SIZE - 1) {
        high_index = low_index;
        low_index = find_largest(bank, -1, high_index + 1);
    }

    return bank[high_index] * 10 + bank[low_index];
};

int main() {
    int sum = 0;
    for (BankArray& bank : load_banks()) {
        int max_joltage = get_max_joltage(bank);
        sum += max_joltage;
    }
    std::cout << "max: " << sum;

    return 0;
}
