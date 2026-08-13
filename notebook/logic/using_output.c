#include "fossil/io/output.h"
#include "fossil/io/input.h"
#include "fossil/io/filesys.h"

int main(void)
{
    char buffer[256];
    fossil_io_filesys_file_t file;

    /**
     * Demonstrate basic output.
     * This includes printing messages, formatted output, and styled text.
     */
    fossil_io_puts("Welcome to Fossil I/O Output!\n");

    /**
     * Demonstrate styled output.
     * This shows how to print messages with ANSI color and style codes.
     */
    fossil_io_printf("{green,bold}Status:{normal} All systems operational.\n");
    fossil_io_printf("{yellow}Warning:{normal} Low disk space.\n");
    fossil_io_printf("{red,bold}Error:{normal} File not found.\n");

    /**
     * Demonstrate primitive types with stream operators.
     * This shows how to print integers and floating-point numbers.
     */
    fossil_io_putchar('>');
    fossil_io_putchar(' ');
    fossil_io_puts("Prompt ready.\n");

    /**
     * Demonstrate formatting into a buffer.
     * This shows how to use snprintf to format strings safely.
     */
    fossil_io_snprintf(
        buffer,
        sizeof(buffer),
        "User: %s, Score: %d",
        "Alice",
        95);
    fossil_io_printf("Formatted buffer: {cyan}%s{normal}\n", buffer);

    /**
     * Demonstrate formatting with ANSI markup.
     * This shows how to apply ANSI color and style codes to formatted strings.
     */
    fossil_io_sprintf(
        buffer,
        "{blue,bold}Build %d successful!{normal}",
        42);
    fossil_io_puts(buffer);
    fossil_io_putchar('\n');

    /**
     * Demonstrate drawing lines.
     * This shows how to draw horizontal and vertical lines in the terminal.
     */
    fossil_io_draw_horizontal_line(40, '=');
    fossil_io_putchar('\n');

    fossil_io_puts("Vertical line:\n");
    fossil_io_draw_vertical_line(5, '|');

    /**
     * Flush buffered output.
     * This ensures all pending output is written to the terminal.
     */
    fossil_io_flush();

    /**
     * Write plain text to a file.
     * This demonstrates saving output to a file without ANSI codes.
     */
    if (fossil_io_filesys_file_open(&file, "output.log", "w") == 0)
    {
        fossil_io_fputs(
            &file,
            "{green}This text is saved without ANSI codes.{normal}\n");

        fossil_io_fprintf(
            &file,
            "Build number: %d\n",
            42);

        fossil_io_filesys_file_close(&file);
    }

    /**
     * Terminal UI control.
     * This demonstrates hiding the cursor, clearing the screen, and moving the cursor.
     */
    fossil_io_hide_cursor();
    fossil_io_clear_screen();
    fossil_io_move_cursor(2, 10);
    fossil_io_printf("{cyan,bold}Fossil TUI Demo{normal}");
    fossil_io_move_cursor(4, 5);
    fossil_io_puts("Rendering complete.");
    fossil_io_move_cursor(6, 1);
    fossil_io_show_cursor();

    return 0;
}
