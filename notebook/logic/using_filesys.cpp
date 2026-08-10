#include "fossil/io/filesys.h"
#include "fossil/io/output.h"

#include <cstring>
#include <cstdlib>

using namespace fossil::io;

int main()
{
    fossil_io_filesys_file_t file;
    char cwd[FOSSIL_FILESYS_MAX_PATH];
    char path[FOSSIL_FILESYS_MAX_PATH];

    /**
     * Demonstrate basic filesystem operations.
     * This includes creating directories, writing files, and checking file properties.
     */
    if (fossil_io_filesys_getcwd(cwd, sizeof(cwd)) == 0)
    {
        out << "Current directory: {cyan}" << cwd << "{normal}\n";
    }

    /**
     * Demonstrate directory creation and file writing.
     * This shows how to create a directory tree and write a file within it.
     */
    fossil_io_filesys_dir_create("project/assets", true);

    /**
     * Demonstrate file writing and reading.
     * This shows how to write to a file and check its readability.
     */
    if (fossil_io_filesys_file_open(
            &file,
            "project/assets/config.txt",
            "w") == 0)
    {
        const char *text = "version=1.0\n";
        fossil_io_filesys_file_write(
            &file,
            text,
            1,
            std::strlen(text));

        fossil_io_filesys_file_close(&file);
    }

    /**
     * Demonstrate file readability check.
     * This shows how to check if a file is readable.
     */
    if (fossil_io_filesys_file_is_readable(
            "project/assets/config.txt") == 1)
    {
        out << "{green}Configuration file is readable.{normal}\n";
    }

    /**
     * Demonstrate absolute path resolution.
     * This shows how to resolve the absolute path of a file.
     */
    if (fossil_io_filesys_abspath(
            "project/assets/config.txt",
            path,
            sizeof(path)) == 0)
    {
        out << "Absolute path: " << path << std::endl;
    }

    /**
     * Demonstrate directory mirroring.
     * This shows how to create a copy of a directory tree.
     */
    fossil_io_filesys_dir_mirror(
        "project",
        "project_backup",
        true);

    /**
     * Demonstrate symbolic link creation.
     * This shows how to create a symbolic link to a file.
     */
    fossil_io_filesys_link_create(
        "project/assets/config.txt",
        "project/current-config.txt",
        true);

    /**
     * Demonstrate file format detection.
     * This shows how to detect the format of a file.
     */
    char format[64];
    if (fossil_io_filesys_file_format(
            "project/assets/config.txt",
            format,
            sizeof(format)) == 0)
    {
        out << "Detected format: {yellow}"
            << format
            << "{normal}\n";
    }

    /**
     * Demonstrate file hashing.
     * This shows how to compute the hash of a file.
     */
    unsigned char hash[32];
    if (fossil_io_filesys_file_hash(
            "project/assets/config.txt",
            hash,
            sizeof(hash),
            "sha256") == 0)
    {
        out << "{green}SHA-256 hash computed successfully.{normal}\n";
    }

    /**
     * Demonstrate directory moving.
     * This shows how to move a directory to a new location.
     */
    fossil_io_filesys_move(
        "project_backup",
        "archive/project_backup");

    /**
     * Demonstrate transactional file operations.
     * This shows how to perform a series of file operations as a single transaction.
     */
    if (fossil_io_filesys_tx_begin() == 0)
    {
        fossil_io_filesys_copy(
            "project/assets/config.txt",
            "project/assets/config.bak",
            true);

        fossil_io_filesys_tx_commit();
    }

    /**
     * Demonstrate symbolic link removal.
     * This shows how to remove a symbolic link.
     */
    fossil_io_filesys_link_remove(
        "project/current-config.txt");

    /**
     * Demonstrate path normalization.
     * This shows how to normalize a file path.
     */
    char *normalized =
        fossil_io_filesys_path_normalize(
            "./project//assets/../assets/config.txt");

    if (normalized)
    {
        out << "Normalized path: "
            << normalized
            << std::endl;
        std::free(normalized);
    }

    return 0;
}
