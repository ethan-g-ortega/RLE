#include <string>
#include <cstdlib>
#include "rle.h"
#include <iostream>

// use string_view since we are not mutating. My doing this we aren't making any copies.
std::string rle_encode(std::string_view in)
{
    int count = 0;
    char current = in[0];
    std::string encoded = "";
    size_t i = 0;

    while (i <= in.size())
    {
        if (std::isdigit(static_cast<unsigned char>(in[i])))
        {
            return "";
        }

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
    const size_t n = in.size();
    std::string decoded;

    std::string digit;
    size_t num = 0; // parsed count
    char c = '\0';

    while (i < n)
    {
        // Must start with at least one digit
        if (!std::isdigit(static_cast<unsigned char>(in[i])))
            return "";

        // Reset for this run
        digit.clear();
        num = 0;

        // Accumulate digits
        while (i < n && std::isdigit(static_cast<unsigned char>(in[i])))
        {
            const unsigned d = static_cast<unsigned>(in[i] - '0'); // one digit at a time
            // if (num*10 + d) would overflow size_t -> malformed
            if (num > (std::numeric_limits<size_t>::max() - d) / 10)
                return "";
            num = num * 10 + d;

            digit.push_back(in[i]);
            ++i;
        }

        if (num == 0)
            return ""; // zero-length runs not allowed
        if (i >= n)
            return ""; // count with no following char

        c = in[i];
        ++i;

        // Gavoid huge allocations/overflow
        if (decoded.size() > decoded.max_size() - num)
            return "";

        // Append num copies of c
        decoded.append(num, c);
    }

    return decoded;
}