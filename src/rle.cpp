#include <string>
#include <cstdlib>
#include "rle.h"
#include <iostream>
#include <limits>
#include <cstddef>

// use string_view since we are not mutating. My doing this we aren't making any copies.
std::string rle_encode(std::string_view in)
{
    int count = 0;
    char current = in[0];
    std::string encoded = "";
    // size_t is an unsigned int type. It is guaranteed to be large enough to hold the size of any object in memory
    // It is platform dependent and will be at least as wide as a pointer on the given architecture
    //(e.g., 32-bit on 32-bit systems, 64-bit on 64-bit systems).
    std::size_t i = 0;

    while (i <= in.size())
    {
        // check if a number is input. return nothing if given
        if (std::isdigit(static_cast<unsigned char>(in[i])))
        {
            return "";
        }
        // counter for number of current character
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
    std::size_t i = 0;
    const std::size_t n = in.size();
    std::string decoded;

    std::string digit;
    std::size_t num = 0; // parsed count
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