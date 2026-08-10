#include <iostream>
#include <vector>
#include <stdexcept>
#include "fossil/io/cstring.h"

using fossil::io::CString;

int main()
{
    try
    {
        /**
         * Demonstrate basic CString operations.
         * This includes creation, trimming, case conversion, and length retrieval.
         */
        CString text("  Fossil Logic SDK CString Demo  ");

        std::cout << "Original: [" << text.str() << "]\n";
        std::cout << "Length:   " << text.length() << "\n";

        /**
         * Demonstrate trimming of whitespace from both ends of the string.
         * This operation modifies the CString in place to remove leading and trailing spaces.
         */
        text.trim();
        std::cout << "Trimmed:  [" << text.str() << "]\n";

        /**
         * Demonstrate case conversion.
         * This shows how to convert the string to upper and lower case.
         */
        CString upper = text.to_upper();
        CString lower = text.to_lower();

        std::cout << "Upper:    " << upper.str() << "\n";
        std::cout << "Lower:    " << lower.str() << "\n";

        /**
         * Demonstrate substring and replacement operations.
         * This includes replacing a substring and extracting a portion of the string.
         */
        CString replaced = text.replace("Fossil", "Copper");
        CString sub = text.substring(0, 6);

        std::cout << "Replaced: " << replaced.str() << "\n";
        std::cout << "Substr:   " << sub.str() << "\n";

        /**
         * Demonstrate search operations.
         * This shows how to check for the presence of a substring and verify if the string starts or ends with a specific value.
         */
        std::cout << "Contains 'Logic': "
                  << (text.contains("Logic") ? "true" : "false") << "\n";

        std::cout << "Starts with 'Fossil': "
                  << (text.starts_with("Fossil") ? "true" : "false") << "\n";

        std::cout << "Ends with 'Demo': "
                  << (text.ends_with("Demo") ? "true" : "false") << "\n";

        /**
         * Demonstrate string transformations.
         * This shows various ways to transform the string.
         */
        CString fun("Fossil Logic");

        std::cout << "ROT13:       " << fun.rot13().str() << "\n";
        std::cout << "Mocking:     " << fun.mocking().str() << "\n";
        std::cout << "Upper Snake: " << fun.upper_snake().str() << "\n";
        std::cout << "Reverse:     " << fun.reverse().str() << "\n";
        std::cout << "Shuffle:     " << fun.shuffle().str() << "\n";

        /**
         * Demonstrate static helper functions.
         * This shows various ways to use static methods for string manipulation.
         */
        std::cout << "Number words (123): "
                  << CString::number_to_words(123) << "\n";

        std::cout << "Parse words: "
                  << CString::number_from_words("one hundred twenty-three") << "\n";

        std::cout << "Money: " << CString::money_to_string(42.50) << "\n";
        std::cout << "Currency: " << CString::currency_to_string(99.99, "$") << "\n";

        /**
         * Demonstrate join and split operations.
         * This shows how to combine and separate strings.
         */
        std::vector<std::string> words = {"Copper", "Script", "Engine"};

        CString joined = CString::join(words, ' ');
        std::cout << "Joined: " << joined.str() << "\n";

        size_t count = 0;
        std::vector<std::string> split = joined.split(' ', &count);

        std::cout << "Split parts (" << count << "):\n";
        for (const auto &s : split)
            std::cout << "  - " << s << "\n";

        /**
         * Demonstrate repeat operation.
         * This shows how to repeat a string a specified number of times.
         */
        CString laugh("ha");
        CString repeated = laugh.repeat(4);

        std::cout << "Repeat: " << repeated.str() << "\n";

        /**
         * Demonstrate JSON helpers.
         * This shows how to escape and unescape JSON strings.
         */
        CString json(R"({"msg":"Hello\nWorld"})");

        CString escaped = json.escape_json();
        CString unescaped = escaped.unescape_json();

        std::cout << "Escaped JSON:   " << escaped.str() << "\n";
        std::cout << "Unescaped JSON: " << unescaped.str() << "\n";

        /**
         * Demonstrate formatting.
         * This shows how to format a string with placeholders.
         */
        CString formatted = CString::format("Engine: %s v%d.%d",
                                            "Fossil",
                                            1,
                                            0);

        std::cout << "Formatted: " << formatted.str() << "\n";

        /**
         * Demonstrate appending to a CString.
         * This shows how to append additional text to an existing CString.
         */
        CString msg("Hello");
        msg.append(", Fossil!");

        std::cout << "Appended: " << msg.str() << "\n";

        /**
         * Demonstrate safe operations.
         * This shows how to perform operations that ensure buffer safety.
         */
        CString safe = CString::copy_safe("Safe CString Example");

        std::cout << "Safe substring: "
                  << safe.substring_safe(5, 7, 64).str() << "\n";

        std::cout << "Safe reverse: "
                  << safe.reverse_safe(64).str() << "\n";

        /**
         * Demonstrate safe contains check.
         * This shows how to check for the presence of a substring in a safe manner.
         */
        std::cout << "Safe contains 'CString': "
                  << (safe.contains_safe("CString", 64) ? "true" : "false") << "\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
