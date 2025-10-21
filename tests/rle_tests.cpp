#include <gtest/gtest.h>
#include "../src/rle.h"

TEST(RLE_Encode, Basic)
{
    EXPECT_EQ(rle_encode(""), "");
    EXPECT_EQ(rle_encode("A"), "1A");
    EXPECT_EQ(rle_encode("AA"), "2A");
    EXPECT_EQ(rle_encode("AB"), "1A1B");
    EXPECT_EQ(rle_encode("AAAABBBCCDAA"), "4A3B2C1D2A");
}

TEST(RLE_Decode, Basic)
{
    EXPECT_EQ(rle_decode(""), "");
    EXPECT_EQ(rle_decode("1A"), "A");
    EXPECT_EQ(rle_decode("2A"), "AA");
    EXPECT_EQ(rle_decode("1A1B"), "AB");
    EXPECT_EQ(rle_decode("4A3B2C1D2A"), "AAAABBBCCDAA");
}

TEST(RLE_RoundTrip, EncodeThenDecode)
{
    std::string original = "AAAABBBCCDAA";
    auto enc = rle_encode(original);
    auto dec = rle_decode(enc);
    EXPECT_EQ(dec, original);
}

TEST(RLE_Decode, MalformedReturnsEmpty)
{
    EXPECT_EQ(rle_decode("A"), "");                          // no count
    EXPECT_EQ(rle_decode("0A"), "");                         // zero not allowed
    EXPECT_EQ(rle_decode("12"), "");                         // count without a char
    EXPECT_EQ(rle_decode("9999999999999999999999999A"), ""); // overflow path
}
