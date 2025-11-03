#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <stdexcept>

unsigned int get_expected_bytes_count(unsigned char x) {
    if (x < 0x80) {
        // 1-byte character 0xxxxxxx
        return 1;
    } else if ((x >> 5) == 0b110) {
        // 2-byte character 110xxxxx 10xxxxxx
        return 2;
    } else if ((x >> 4) == 0b1110) {
        // 3-byte character 1110xxxx 10xxxxxx 10xxxxxx
        return 3;
    } else if ((x >> 3) == 0b11110) {
        // 4-byte character 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
        return 4;
    }
    // invalid leading byte
    throw std::runtime_error("Invalid UTF-8 leading byte");
    return 0;
}

char32_t decodeUTF(const std::vector<unsigned char> *bytes, int *cur_byte_index, unsigned int *expected_bytes_count) {
    char32_t code_point = 0;
    if (*expected_bytes_count == 1) {
        code_point |= (*bytes)[*cur_byte_index] & 0b01111111;
    }
    else if (*expected_bytes_count == 2) {
        code_point |= ((*bytes)[*cur_byte_index] & 0b00011111) << 6;
        code_point |= ((*bytes)[*cur_byte_index + 1] & 0b00111111);
    }
    else if (*expected_bytes_count == 3) {
        code_point |= ((*bytes)[*cur_byte_index] & 0b00001111) << 12;
        code_point |= ((*bytes)[*cur_byte_index + 1] & 0b00111111) << 6;
        code_point |= ((*bytes)[*cur_byte_index + 2] & 0b00111111);
    }
    else if (*expected_bytes_count == 4) {
        code_point |= ((*bytes)[*cur_byte_index] & 0b00000111) << 18;
        code_point |= ((*bytes)[*cur_byte_index + 1] & 0b00111111) << 12;
        code_point |= ((*bytes)[*cur_byte_index + 2] & 0b00111111) << 6;
        code_point |= ((*bytes)[*cur_byte_index + 3] & 0b00111111);
    }
    return code_point;
}

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
        unsigned int expected_bytes_count = get_expected_bytes_count(bytes[cur_byte_index]);
        char32_t code_point =  decodeUTF(&bytes, &cur_byte_index, &expected_bytes_count);
        code_points.push_back(code_point);

        // skip to the next unicode byte
        cur_byte_index += expected_bytes_count;
    }

    return 0;
}