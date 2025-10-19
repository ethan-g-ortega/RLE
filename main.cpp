/*
Encoding format: <count><char> where <count> is a positive integer in decimal and <char> is exactly one byte from the input. Counts of 1 must still be written (so AB → 1A1B). Decoding must reconstruct the original exactly.
Input is arbitrary bytes (assume ASCII for now).
If decoding sees malformed input (e.g., missing count, overflow, or count with no following char), return an empty string or throw—your choice, but be consistent and document it.
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>

// use string_view since we are not mutating. My doing this we aren't making any copies.
std::string rle_encode(std::string_view in)
{
    // if (in.empty())
    // {
    //     return {};
    // }
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
    // if (in.empty())
    // {
    //     return {};
    // }

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

int main(int argc, char *argv[])
{

    std::string test(argv[1]);
    auto start = std::chrono::high_resolution_clock::now();
    std::string res = rle_encode(test);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
    std::cout << res << std::endl;
    start = std::chrono::high_resolution_clock::now();
    std::string res2 = rle_decode(res);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
    std::cout << res2 << std::endl;

    return 0;
}