#include "fossil/io/archive.h"
#include "fossil/io/output.h"

int main()
{
    using fossil::io::Archive;

    /** 
     * Open an archive file in read mode with normal compression.
     * This opens "assets.zip" as a ZIP archive with read-only access
     * and applies normal compression level to the operation.
     */
    Archive archive(
        "assets.zip",
        FOSSIL_IO_ARCHIVE_ZIP,
        FOSSIL_IO_ARCHIVE_READ,
        FOSSIL_IO_COMPRESSION_NORMAL
    );

    /** 
     * Check if archive was successfully opened.
     * If the archive is not valid, it indicates the open operation failed,
     * so we print an error message and exit the program with status code 1.
     */
    if (!archive.is_valid())
    {
        fossil::io::Output::printf("Failed to open archive\n");
        return 1;
    }

    /** 
     * Display the contents of the archive.
     * This prints a human-readable listing of all entries (files/folders)
     * contained within the archive to standard output.
     */
    fossil::io::Output::printf("Archive contents:\n");
    archive.print();

    /** 
     * Check if a specific file exists in the archive.
     * This searches for "readme.txt" within the archive and confirms
     * its presence before attempting to access it.
     */
    if (archive.exists("readme.txt"))
    {
        fossil::io::Output::printf("readme.txt exists\n");
    }

    /** 
     * Retrieve the size of a specific file from the archive.
     * This obtains the uncompressed size (in bytes) of the "readme.txt" file
     * stored in the archive and stores it in the ssize_t variable.
     */
    ssize_t size = archive.entry_size("readme.txt");

    /** 
     * Print the file size in bytes.
     * This displays the retrieved size value using printf-style formatting
     * with the %zd specifier for ssize_t types.
     */
    fossil::io::Output::printf("Size: %zd bytes\n", size);

    return 0;
}
