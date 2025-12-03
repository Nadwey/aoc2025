#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

std::filesystem::path get_souce_dir() {
    return std::filesystem::path(__FILE__).parent_path();
}

struct Range {
    uint64_t min;
    uint64_t max;
};

std::vector<Range> load_ids() {
    std::ifstream input_file(get_souce_dir().append("input.txt"));

    std::vector<Range> out;

    auto read_number = [&input_file] {
        uint64_t num = 0;
        char c;

        while (true) {
            input_file.read(&c, 1);
            // check if a number
            if (input_file.eof() || (c < 48 || c > 57)) {
                break;
            }
            num *= 10ull;
            num += c - 48ull;
        }

        return num;
    };

    while (!input_file.eof()) {
        uint64_t min = read_number();
        uint64_t max = read_number();

        if (min != 0 && max != 0) {
            out.push_back(Range{ min, max });
        }
    }

    return out;
}

int count_digits(uint64_t number) {
    int digits = 0;

    while (number != 0ull) {
        number /= 10ull;
        digits++;
    }

    return digits;
}

unsigned int quick_10pow(int exp) {
    unsigned int out = 1;
    while (exp-- > 0) {
        out *= 10;
    }
    return out;
}

bool is_invalid(uint64_t number) {
    int digits = count_digits(number);

    // numbers with odd number of digits can't only consist of 2 repeating segments
    if (digits % 2 == 1) {
        return false;
    }

    unsigned int div = quick_10pow(digits / 2);

    unsigned int low = number % div;
    unsigned int high = (number / div);

    return low == high;
}

int main() {
    uint64_t sum = 0;
    for (Range range : load_ids()) {
        for (uint64_t i = range.min; i <= range.max; i++) {
            sum += is_invalid(i) ? i : 0ull;
        }
    }

    std::cout << "sum: " << sum << std::endl;
}