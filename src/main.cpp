#include "rle.h"
#include <iostream>
#include <string>
// command line program. accept string to encode nad decode
int main(int argc, char *argv[])
{
    // only one string to be encoded and decoded at a time
    if (argc < 2)
    {
        // cerr immediately flushes immediately to the opearting systems so the error message is shown before the program crashes
        //  it is unbuffered, unlike cout
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
