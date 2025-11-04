#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>

#include "utf/utf_utils.h"


int main(int argc, char* argv[]) {
    std::ifstream file(argv[1], std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << argv[1] << std::endl;
        return 1;
    }

    // pass file begin iterator and null iterator to vector constructor
    // it will copy every byte in between into the vector
    std::vector<unsigned char> bytes{
        std::istreambuf_iterator<char>(file),
        std::istreambuf_iterator<char>()
    };

    std::vector<char32_t> code_points;
    for (int cur_byte_index = 0; cur_byte_index < (int)bytes.size();) {
        // calc how many bytes this unicode character need
        unsigned int expected_bytes_count = utf8_expected_bytes(bytes[cur_byte_index]);
        char32_t code_point = utf8_decode(bytes, cur_byte_index, expected_bytes_count);
        code_points.push_back(code_point);

        // skip to the next unicode byte
        cur_byte_index += expected_bytes_count;
    }

    return 0;
}