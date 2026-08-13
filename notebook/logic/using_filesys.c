#include "fossil/io/filesys.h"
#include "fossil/io/output.h"

int main(void)
{
    fossil_io_filesys_file_t file;
    fossil_io_filesys_obj_t entries[32];
    size_t entry_count = 0;
    char cwd[FOSSIL_FILESYS_MAX_PATH];
    char abs_path[FOSSIL_FILESYS_MAX_PATH];
    char dirname[FOSSIL_FILESYS_MAX_PATH];
    char basename[FOSSIL_FILESYS_MAX_PATH];
    char extension[32];
    char buffer[256];
    const char *parts[] = {
        "archive.part001",
        "archive.part002"
    };

    /**
     * Demonstrate basic filesystem operations.
     * This includes creating directories, writing files, and checking file properties.
     */
    if (fossil_io_filesys_getcwd(cwd, sizeof(cwd)) == 0)
    {
        fossil_io_printf("Current directory: {cyan}%s{normal}\n", cwd);
    }

    /**
     * Demonstrate directory creation.
     * This shows how to create a directory tree.
     */
    fossil_io_filesys_dir_create("data/logs", true);

    /**
     * Demonstrate file writing.
     * This shows how to open a file for writing and write content to it.
     */
    if (fossil_io_filesys_file_open(&file, "data/logs/app.log", "w") == 0)
    {
        const char *message = "Fossil Filesystem API example.\n";
        fossil_io_filesys_file_write(
            &file,
            message,
            1,
            strlen(message));

        fossil_io_filesys_file_flush(&file);
        fossil_io_filesys_file_close(&file);
    }

    /**
     * Demonstrate file existence and metadata checking.
     * This shows how to check if a file exists and retrieve its metadata.
     */
    if (fossil_io_filesys_exists("data/logs/app.log") == 1)
    {
        fossil_io_printf("{green}File created successfully.{normal}\n");
    }

    fossil_io_filesys_obj_t info;
    if (fossil_io_filesys_stat("data/logs/app.log", &info) == 0)
    {
        fossil_io_printf(
            "Type: %s, Size: %d bytes\n",
            fossil_io_filesys_type_string(info.type),
            (int)info.size);
    }

    /**
     * Demonstrate path utilities.
     * This shows how to work with file paths.
     */
    fossil_io_filesys_abspath("data/logs/app.log", abs_path, sizeof(abs_path));
    fossil_io_filesys_dirname(abs_path, dirname, sizeof(dirname));
    fossil_io_filesys_basename(abs_path, basename, sizeof(basename));
    fossil_io_filesys_extension(abs_path, extension, sizeof(extension));

    fossil_io_printf("Absolute path: %s\n", abs_path);
    fossil_io_printf("Directory: %s\n", dirname);
    fossil_io_printf("Filename: %s\n", basename);
    fossil_io_printf("Extension: %s\n", extension);

    /**
     * Demonstrate path normalization.
     * This shows how to normalize a file path.
     */
    char *normalized =
        fossil_io_filesys_path_normalize("./data//logs/../logs/app.log");
    if (normalized)
    {
        fossil_io_printf("Normalized path: %s\n", normalized);
        free(normalized);
    }

    /**
     * Demonstrate file copying and moving.
     * This shows how to copy and move files.
     */
    fossil_io_filesys_copy(
        "data/logs/app.log",
        "data/logs/app-copy.log",
        true);

    fossil_io_filesys_move(
        "data/logs/app-copy.log",
        "data/logs/app-moved.log");

    /**
     * Demonstrate symbolic link creation.
     * This shows how to create a symbolic link to a file.
     */
    fossil_io_filesys_link_create(
        "data/logs/app.log",
        "data/logs/latest.log",
        true);

    /**
     * Demonstrate symbolic link reading.
     * This shows how to read the target of a symbolic link.
     */
    if (fossil_io_filesys_link_read(
            "data/logs/latest.log",
            buffer,
            sizeof(buffer)) == 0)
    {
        fossil_io_printf("Link target: %s\n", buffer);
    }

    /**
     * Demonstrate directory listing.
     * This shows how to list the contents of a directory.
     */
    if (fossil_io_filesys_dir_list(
            "data/logs",
            entries,
            32,
            &entry_count) == 0)
    {
        fossil_io_printf(
            "\n{bold}Directory listing (%d entries):{normal}\n",
            (int)entry_count);

        for (size_t i = 0; i < entry_count; ++i)
        {
            fossil_io_printf(
                " - %s (%s)\n",
                entries[i].path,
                fossil_io_filesys_type_string(entries[i].type));
        }
    }

    /**
     * Demonstrate file split and join.
     * This shows how to split a file into parts and join them back together.
     */
    fossil_io_filesys_file_split(
        "data/logs/app.log",
        10,
        "archive.part");

    fossil_io_filesys_file_join(
        parts,
        2,
        "archive-restored.log");

    /**
     * Demonstrate transactional file operations.
     * This shows how to perform a series of file operations as a single transaction.
     */
    if (fossil_io_filesys_tx_begin() == 0)
    {
        fossil_io_filesys_copy(
            "data/logs/app.log",
            "data/logs/backup.log",
            true);

        fossil_io_filesys_tx_commit();
    }

    /**
     * Demonstrate cleanup.
     * This shows how to remove temporary files and links.
     */
    fossil_io_filesys_link_remove("data/logs/latest.log");
    fossil_io_filesys_remove("archive-restored.log", false);

    return 0;
}
