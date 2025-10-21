#include "rle.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: ./rle_app <string>\n";
        return 1;
    }
    std::string input = argv[1];
    std::string encoded = rle_encode(input);
    std::string decoded = rle_decode(encoded);

    std::cout << "encoded: " << encoded << "\n";
    std::cout << "decoded: " << decoded << "\n";
    return 0;
}
