#include "fossil/io/archive.h"
#include "fossil/io/output.h"

int main(void)
{
    /** 
     * Open an archive file in read mode with normal compression.
     * This opens "assets.zip" as a ZIP archive with read-only access
     * and applies normal compression level to the operation.
     */
    fossil_io_archive_t *archive =
        fossil_io_archive_open(
            "assets.zip",
            FOSSIL_IO_ARCHIVE_ZIP,
            FOSSIL_IO_ARCHIVE_READ,
            FOSSIL_IO_COMPRESSION_NORMAL
        );

    /** 
     * Check if archive was successfully opened.
     * If the archive pointer is NULL, it indicates the open operation failed,
     * so we print an error message and exit the program with status code 1.
     */
    if (!archive)
    {
        fossil_io_output_print("Failed to open archive\n");
        return 1;
    }

    /** 
     * Display the contents of the archive.
     * This prints a human-readable listing of all entries (files/folders)
     * contained within the archive to standard output.
     */
    fossil_io_output_print("Archive listing:\n");
    fossil_io_archive_print(archive);

    /** 
     * Check if a specific file exists in the archive.
     * This searches for "readme.txt" within the archive and confirms
     * its presence before attempting to access it.
     */
    if (fossil_io_archive_exists(archive, "readme.txt"))
    {
        fossil_io_output_print("readme.txt exists\n");
    }

    /** 
     * Retrieve the size of a specific file from the archive.
     * This obtains the uncompressed size (in bytes) of the "readme.txt" file
     * stored in the archive and stores it in the ssize_t variable.
     */
    ssize_t size = fossil_io_archive_entry_size(archive, "readme.txt");

    /** 
     * Print the file size in bytes.
     * This displays the retrieved size value using printf-style formatting
     * with the %zd specifier for ssize_t types.
     */
    fossil_io_printf("Size: %zd bytes\n", size);

    /** 
     * Close the archive and free associated resources.
     * This properly releases all memory and file handles allocated during
     * the archive opening and processing to prevent resource leaks.
     */
    fossil_io_archive_close(archive);

    return 0;
}
