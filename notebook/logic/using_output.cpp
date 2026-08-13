#include "fossil/io/output.h"
#include "fossil/io/input.h"
#include "fossil/io/filesys.h"

#include <iostream>
#include <string>

using namespace fossil::io;

int main()
{
    char buffer[256];
    fossil_io_filesys_file_t file;

    /**
     * Demonstrate basic output.
     * This includes printing messages, formatted output, and styled text.
     */
    out << "Welcome to Fossil I/O Output!" << std::endl;

    /**
     * Demonstrate styled output.
     * This shows how to print messages with ANSI color and style codes.
     */
    Output::printf("{green,bold}Status:{normal} All systems OK\n");
    Output::printf("{yellow}Warning:{normal} CPU usage high\n");
    Output::printf("{red,bold}Error:{normal} Unable to connect\n");

    /**
     * Demonstrate primitive types with stream operators.
     * This shows how to print integers and floating-point numbers.
     */
    out << "Build number: " << 42 << std::endl;
    out << "Temperature: " << 23.75 << std::endl;

    /**
     * Demonstrate formatting into a buffer.
     * This shows how to use snprintf to format strings safely.
     */
    Output::snprintf(
        buffer,
        sizeof(buffer),
        "User: %s, Level: %d",
        "Bob",
        7);

    out << "Buffer contents: {cyan}" << buffer << "{normal}" << std::endl;

    /* Format with ANSI markup applied */
    Output::sprintf(
        buffer,
        "{magenta,bold}Deployment successful!{normal}");

    out << buffer << std::endl;

    /**
     * Demonstrate drawing lines.
     * This shows how to draw horizontal and vertical lines in the terminal.
     */
    Output::draw_horizontal_line(50, '-');
    out << std::endl;

    out << "Vertical separator:" << std::endl;
    Output::draw_vertical_line(4, '|');

    /**
     * Flush buffered output.
     * This ensures all pending output is written to the terminal.
     */
    if (fossil_io_filesys_file_open(&file, "report.txt", "w") == 0)
    {
        Output::fputs(
            &file,
            "{green}Report generated successfully.{normal}\n");

        Output::fprintf(
            &file,
            "Processed records: %d\n",
            1024);

        fossil_io_filesys_file_close(&file);
    }

    /**
     * Terminal UI control.
     * This demonstrates hiding the cursor, clearing the screen, and moving the cursor.
     */
    Output::hide_cursor();
    Output::clear_screen();
    Output::move_cursor(3, 8);
    Output::printf("{blue,bold}Dashboard{normal}\n");
    Output::move_cursor(5, 4);
    out << "Loading complete." << std::endl;
    Output::move_cursor(7, 1);
    Output::show_cursor();

    /* Flush output */
    Output::flush();

    return 0;
}
