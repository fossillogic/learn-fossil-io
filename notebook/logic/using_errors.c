#include "fossil/io/error.h"
#include "fossil/io/output.h"

int main(void)
{
    const char *code = "io.read";

    /**
     * Retrieve the numeric ID associated with the error code.
     * This ID can be used for programmatic error handling.
     */
    int id = fossil_io_code(code);

    /**
     * Retrieve the symbolic message associated with the error code.
     * This message can be used for logging or user-facing error reporting.
     */
    const char *message = fossil_io_what(code);

    /**
     * Print the error information using the Fossil output library.
     * This demonstrates how to use the Output class for formatted output.
     */
    fossil_io_printf("Error code: %s\n", code);
    fossil_io_printf("Error ID: %d\n", id);
    fossil_io_printf("Description: %s\n", message);

    /**
     * Report an error using the Fossil error reporting mechanism.
     * This will log the error and may trigger additional error handling.
     */
    fossil_io_error("[%s] %s", code, message);

    /**
     * Example control flow based on error code.
     * This demonstrates how to handle different error codes in a switch statement.
     */
    switch (fossil_io_code("memory.alloc"))
    {
        case 0:
            /**
             * Handle the case where there is no error.
             * This may involve normal program execution or specific actions for a successful operation.
             */
            fossil_io_printf("No error.\n");
            break;

        default:
            fossil_io_printf("An error was detected.\n");
            break;
    }

    return 0;
}
