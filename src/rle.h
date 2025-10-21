#pragma once
#include <string>
#include <string_view>

// Encoding format: <count><char>, counts of 1 must be written (AB -> 1A1B).
// Input/Output are arbitrary bytes treated as chars (assume ASCII).
// On malformed decode input, returns empty string (documented behavior).
std::string rle_encode(std::string_view in);
std::string rle_decode(std::string_view in);
