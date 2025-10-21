#include <string>
#include <cstdlib>
#include "rle.h"

// use string_view since we are not mutating. My doing this we aren't making any copies.
std::string rle_encode(std::string_view in)
{
    int count = 0;
    char current = in[0];
    std::string encoded = "";
    size_t i = 0;

    while (i <= in.size())
    {
        if (in[i] == current)
        {
            count += 1;
        }
        else
        {
            encoded += std::to_string(count) + current;
            current = in[i];
            count = 1;
        }
        i += 1;
    }

    return encoded;
}

std::string rle_decode(std::string_view in)
{
    size_t i = 0;
    std::string decoded = "";
    int num = 0;
    std::string c = "";

    while (i < in.size())
    {
        num = std::stoi(&in[i]);
        i += 1;
        c = in[i];
        i += 1;
        for (int x = 0; x < num; x++)
        {
            decoded += c;
        }
    }
    return decoded;
}