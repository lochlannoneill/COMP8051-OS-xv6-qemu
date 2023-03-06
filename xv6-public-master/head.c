#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"  // xv6 kernel header file for file control options

#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define BUF_SIZE 512
#define LINE_COUNT_MAX 10

int main(int argc, char *argv[]) {
    //trace(1);
    
    int fd;  // file descriptor -> integer value that is used to identify an open file in a program.
    int n;  // number of bytes read from the input file in each line iteration
    char buf[BUF_SIZE];

    if (argc != 2) {  // Input arguments should be 2 -> something like "head example.txt"
        printf(STDERR, "Usage: <%s> <filename>\n", argv[0]);
        exit();
    }

    fd = open(argv[1], O_RDONLY);  // Open file for reading
    if (fd < 0) {  // Check if file opening failed
        printf(STDERR, "Error: cannot open file '%s'\n", argv[1]);
        exit();
    }

    int line_count = 0;
    while ((n = read(fd, buf, BUF_SIZE)) > 0 && line_count < LINE_COUNT_MAX) {  // Read from file until 10 lines or end of file
        for (int i = 0; i < n && line_count < 10; i++) {  // Iterate over the bytes read
            printf(STDOUT, "%c", buf[i]);
            if(buf[i] == '\n') line_count++;
        }
    }

    close(fd);  // Close file before terminating program
    exit();
}

