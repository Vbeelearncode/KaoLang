// utf_utils.h - utility functions for dealing with UTF8-32 encoding/decoding
#pragma once

#include <vector>

unsigned int utf8_expected_bytes(unsigned char first_byte);

char32_t utf8_decode(
    const std::vector<unsigned char> &bytes, 
    int &cur_byte_index, 
    unsigned int expected_bytes_count
);
