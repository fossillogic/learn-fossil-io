#include "fossil/io/output.h"
#include "fossil/io/cipher.h"

using fossil::io::Cipher;

int main()
{
    std::string text = "Hello Fossil Logic";

    /**
     * Encode the text using the specified cipher.
     * This applies the ROT13 transformation to the input string and returns
     * a new string containing the encoded result.
     */
    std::string encoded = Cipher::encode(text, "rot13");
    fossil::io::Output::printf("Encoded: %s\n", encoded.c_str());

    /**
     * Decode the encoded text using the specified cipher.
     * This reverses the ROT13 transformation applied to the encoded string
     * and returns a new string containing the decoded result.
     */
    std::string decoded = Cipher::decode(encoded, "rot13");
    fossil::io::Output::printf("Decoded: %s\n", decoded.c_str());

    /**
     * Additional encoding examples using different ciphers.
     * This demonstrates the use of Base64, Morse code, and Leet Speak
     * transformations on the same input string.
     */
    std::string base64 = Cipher::encode(text, "base64");
    std::string morse  = Cipher::encode(text, "morse");
    std::string leet   = Cipher::encode(text, "leet");

    /**
     * Print the results of the additional encoding examples.
     * This displays the transformed strings for Base64, Morse code, and Leet Speak
     * using printf-style formatting.
     */
    fossil::io::Output::printf("Base64: %s\n", base64.c_str());
    fossil::io::Output::printf("Morse:  %s\n", morse.c_str());
    fossil::io::Output::printf("Leet:   %s\n", leet.c_str());

    /**
     * Round-trip decoding example for Base64.
     * This decodes the previously encoded Base64 string back to its original form
     * and prints the result to verify correctness.
     */
    std::string roundtrip = Cipher::decode(base64, "base64");
    fossil::io::Output::printf("Roundtrip: %s\n", roundtrip.c_str());

    return 0;
}