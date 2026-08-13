#include <string>
#include <cstdarg>
#include "fossil/io/error.h"
#include "fossil/io/output.h"

int main()
{
    using fossil::io::Error;

    std::string code = "memory.alloc";

    /**
     * Retrieve the numeric ID associated with the error code.
     * This ID can be used for programmatic error handling.
     */
    int id = Error::code(code);
    const char* message = Error::what(code);

    /**
     * Print the error information using the Fossil output library.
     * This demonstrates how to use the Output class for formatted output.
     */
    fossil::io::Output::printf("Error code: %s\n", code.c_str());
    fossil::io::Output::printf("Error ID: %d\n", id);
    fossil::io::Output::printf("Description: %s\n", message);

    /**
     * Report an error using the Fossil error reporting mechanism.
     * This will log the error and may trigger additional error handling.
     */
    Error::report("[%s] %s", code.c_str(), message);

    /**
     * Example control flow based on error code.
     * This demonstrates how to handle different error codes in a switch statement.
     */
    fossil::io::Output::printf("\nAdditional examples:\n");
    fossil::io::Output::printf("network.timeout -> ID %d, %s\n",
                               Error::code("network.timeout"),
                               Error::what("network.timeout"));

    /**
     * Example control flow based on error code.
     * This demonstrates how to handle different error codes in a switch statement.
     */
    fossil::io::Output::printf("system.ok -> ID %d, %s\n",
                               Error::code("system.ok"),
                               Error::what("system.ok"));

    /**
     * Example control flow.
     * This demonstrates how to handle different error codes in a switch statement.
     */
    switch (Error::code("fs.not_found"))
    {
        case -1:
            fossil::io::Output::printf("Unknown error code.\n");
            break;

        default:
            fossil::io::Output::printf("Filesystem error recognized.\n");
            break;
    }

    return 0;
}
