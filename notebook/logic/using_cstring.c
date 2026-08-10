#include <stdlib.h>

#include <fossil/io/cstring.h>
#include <fossil/io/error.h>
#include <fossil/io/output.h>

int main(void)
{
    /** 
     * Create a cstring with initial value.
     * This initializes the cstring with the specified string literal.
     */
    cstring greeting = fossil_io_cstring_create("  Hello Fossil IO  ");
    if (!greeting)
    {
        fossil_io_error("[%s] %s",
                        "memory.alloc",
                        fossil_io_what("memory.alloc"));
        return EXIT_FAILURE;
    }

    fossil_io_cstring_trim(greeting);

    /**
     * Convert to upper case and reverse the string.
     * These operations demonstrate the mutating capabilities of cstring.
     */
    cstring upper = fossil_io_cstring_copy(greeting);
    fossil_io_cstring_to_upper(upper);

    cstring reversed = fossil_io_cstring_reverse(
        fossil_io_cstring_copy(greeting));

    /**
     * Print the results to the console.
     * This uses the fossil_io_printf function to display the cstring values.
     */
    fossil_io_printf("{green}Original:{reset} %s\n", greeting);
    fossil_io_printf("{cyan}Upper:{reset} %s\n", upper);
    fossil_io_printf("{magenta}Reverse:{reset} %s\n", reversed);

    /**
     * Demonstrate safe appending to a cstring.
     * This shows how to append additional text while ensuring buffer safety.
     */
    cstring message = fossil_io_cstring_create_safe("Status", 64);
    if (!message)
    {
        fossil_io_error("[%s] %s",
                        "memory.alloc",
                        fossil_io_what("memory.alloc"));
        return EXIT_FAILURE;
    }

    /**
     * Append additional text to the cstring.
     * This operation appends ": OK" to the existing message.
     */
    if (fossil_io_cstring_append_safe(&message, ": OK", 64) != 0)
    {
        fossil_io_error("[%s] %s",
                        "memory.alloc",
                        fossil_io_what("memory.alloc"));
    }
    else
    {
        fossil_io_printf("{bold}{green}%s{reset}\n", message);
    }

    /**
     * Demonstrate money formatting and parsing.
     * This shows how to convert a numeric value to a formatted money string
     * and parse a money string back to a numeric value.
     */
    char money[64];

    if (fossil_io_cstring_money_to_string(1234567.89,
                                          money,
                                          sizeof(money)) == 0)
    {
        fossil_io_printf("{yellow}Money:{reset} %s\n", money);
    }
    else
    {
        fossil_io_error("[%s] %s",
                        "format.invalid",
                        fossil_io_what("format.invalid"));
    }

    /**
     * Parse a money string back to a numeric value.
     * This demonstrates the ability to convert a formatted money string
     * into a double value for further processing.
     */
    double amount = 0.0;
    if (fossil_io_cstring_string_to_money("$1,234.56", &amount) == 0)
    {
        fossil_io_printf("{blue}Parsed amount:{reset} %.2f\n", amount);
    }
    else
    {
        fossil_io_error("[%s] %s",
                        "parse.invalid",
                        fossil_io_what("parse.invalid"));
    }

    /**
     * Demonstrate various string transformations.
     * This includes Pig Latin, Leetspeak, Mocking case, ROT13, and UPPER_SNAKE case.
     */
    cstring piglatin = fossil_io_cstring_create("hello world");
    char piglatin_out[128];

    if (fossil_io_cstring_piglatin(piglatin,
                                   piglatin_out,
                                   sizeof(piglatin_out)) == 0)
    {
        fossil_io_printf("{magenta}Pig Latin:{reset} %s\n", piglatin_out);
    }

    /**
     * Demonstrate Leetspeak transformation.
     * This converts a standard string into its Leetspeak equivalent.
     */
    cstring leet_input = fossil_io_cstring_create("Fossil Logic");
    char leet_out[128];

    if (fossil_io_cstring_leetspeak(leet_input,
                                    leet_out,
                                    sizeof(leet_out)) == 0)
    {
        fossil_io_printf("{red}Leet:{reset} %s\n", leet_out);
    }

    /**
     * Demonstrate Mocking case, ROT13, and UPPER_SNAKE case transformations.
     * These transformations showcase different ways to manipulate string cases.
     */
    cstring mocking = fossil_io_cstring_mocking("this is serious");
    cstring rot13 = fossil_io_cstring_rot13("hello world");
    cstring snake = fossil_io_cstring_upper_snake("Fossil Logic SDK");

    fossil_io_printf("{yellow}Mocking:{reset} %s\n", mocking);
    fossil_io_printf("{yellow}ROT13:{reset} %s\n", rot13);
    fossil_io_printf("{yellow}UPPER_SNAKE:{reset} %s\n", snake);

    /**
     * Demonstrate number word conversion.
     * This shows how to convert between numeric values and their word representations.
     */
    int value = 0;
    if (fossil_io_cstring_number_from_words("twenty-three", &value) == 0)
    {
        fossil_io_printf("{green}Words -> Number:{reset} %d\n", value);
    }

    char words[128];
    if (fossil_io_cstring_number_to_words(42,
                                          words,
                                          sizeof(words)) == 0)
    {
        fossil_io_printf("{green}Number -> Words:{reset} %s\n", words);
    }

    /**
     * Demonstrate case-insensitive string replacement.
     * This replaces occurrences of a substring in a case-insensitive manner.
     */
    cstring replaced = fossil_io_cstring_case_replace(
        "The Fossil SDK is powerful",
        "fossil",
        "Jellyfish");

    fossil_io_printf("{cyan}Replaced:{reset} %s\n", replaced);

    /**
     * Demonstrate error code lookup and description retrieval.
     * This shows how to retrieve the error code ID and its corresponding description.
     */
    const char *code = "network.timeout";
    int code_id = fossil_io_code(code);
    const char *description = fossil_io_what(code);

    fossil_io_printf(
        "{bold}{red}Error Lookup{reset}\n"
        "  Code: %s\n"
        "  ID:   %d\n"
        "  What: %s\n",
        code,
        code_id,
        description);

    /**
     * Demonstrate error reporting.
     * This shows how to report an error with a specific code and description.
     */
    fossil_io_error("[%s] %s", code, description);

    /**
     * Demonstrate JSON escaping and unescaping.
     * This shows how to escape special characters in a JSON string and then unescape it back.
     */
    cstring escaped =
        fossil_io_cstring_escape_json("Hello \"World\"\n");

    cstring unescaped =
        fossil_io_cstring_unescape_json(escaped);

    fossil_io_printf("{blue}Escaped JSON:{reset} %s\n", escaped);
    fossil_io_printf("{blue}Unescaped JSON:{reset} %s\n", unescaped);

    /**
     * Clean up allocated cstrings to prevent memory leaks.
     * This ensures that all dynamically allocated cstrings are properly freed.
     */
    fossil_io_cstring_free(greeting);
    fossil_io_cstring_free(upper);
    fossil_io_cstring_free(reversed);
    fossil_io_cstring_free(message);
    fossil_io_cstring_free(piglatin);
    fossil_io_cstring_free(leet_input);
    fossil_io_cstring_free(mocking);
    fossil_io_cstring_free(rot13);
    fossil_io_cstring_free(snake);
    fossil_io_cstring_free(replaced);
    fossil_io_cstring_free(escaped);
    fossil_io_cstring_free(unescaped);

    return EXIT_SUCCESS;
}
