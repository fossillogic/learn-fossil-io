#include "fossil/io/output.h"
#include "fossil/io/cipher.h"

int main(void)
{
    const char *text = "Hello Fossil";
    const char *cipher = "rot13";

    /** 
     * Encode the text using the specified cipher.
     * This applies the ROT13 transformation to the input string and returns
     * a new string containing the encoded result.
     */
    char *encoded = fossil_io_cipher_encode(text, cipher);

    if (!encoded)
    {
        fossil_io_printf("Encode failed\n");
        return 1;
    }

    fossil_io_printf("Encoded: %s\n", encoded);

    /** 
     * Decode the encoded text using the specified cipher.
     * This reverses the ROT13 transformation applied to the encoded string
     * and returns a new string containing the decoded result.
     */
    char *decoded = fossil_io_cipher_decode(encoded, cipher);

    if (!decoded)
    {
        fossil_io_printf("Decode failed\n");
        free(encoded);
        return 1;
    }

    fossil_io_printf("Decoded: %s\n", decoded);

    /** 
     * Cleanup (IMPORTANT)
     * Free the memory allocated for the encoded and decoded strings.
     */
    free(encoded);
    free(decoded);

    return 0;
}
