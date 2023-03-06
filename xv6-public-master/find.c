#include "types.h"
#include "user.h"
#include "fcntl.h"
#include "stat.h"
#include "fs.h"

#define STDIN 0
#define STDOUT 1
#define STDERR 2

void find(char *path, char *filename)
{
    int fd;
    struct dirent de;
    struct stat st;

    // Open the directory specified by path
    fd = open(path, 0);
    if (fd < 0) {
        // If the directory cannot be opened, print an error message and return
        printf(STDOUT, "find: cannot open %s\n", path);
        return;
    }

    // Get information about the directory
    if (fstat(fd, &st) < 0) {
        // If the directory information cannot be obtained, print an error message and return
        printf(STDOUT, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    switch (st.type) {
        // Case path == file
        // If path is a file and its name matches the given filename -> print the path to STDOUT
        case T_FILE:
            if (strcmp(path + strlen(path) - strlen(filename), filename) == 0)
                printf(STDOUT, "%s\n", path);
            break;

        case T_DIR:
        // Case path == directory
        // Check if the path is too long
            if (strlen(path) + 1 + DIRSIZ + 1 > 512) {
                // If the path is too long, print an error message and return
                printf(STDOUT, "find: path too long: %s\n", path);
                break;
            }

            // If the path doesn't end in a '/', append one to the end of the path
            if (path[strlen(path)-1] != '/') {
                strcpy(path + strlen(path), "/");
            }

            // Loop through the entries in the directory
            while (read(fd, &de, sizeof(de)) == sizeof(de)) {
                // Ignore "." and ".." entries
                if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
                    continue;

                // Append the name of the entry to the path
                strcpy(path + strlen(path), de.name);
                if (stat(path, &st) < 0) {
                    // If the entry information cannot be obtained, print an error message and continue to the next entry
                    printf(STDOUT, "find: cannot stat %s\n", path);
                    continue;
                }

                //DEBUGGING - Indicate that the find function is searching a directory specified by the path parameter.
                //printf(STDOUT, "Searching directory: %s\n", path);

                //Recursively call find with the entry's path
                find(path, filename);

                // Remove the name of the entry from the path
                path[strlen(path) - strlen(de.name)] = '\0';
            }
            break;
    }

    close(fd);
}

int main(int argc, char *argv[])
{
    // Check if the correct number of arguments were provided
    if (argc != 3) {
        printf(STDOUT, "Usage: %s <path> <filename>\n", argv[0]);
        exit();
    }

    find(argv[1], argv[2]);

    exit();
}
