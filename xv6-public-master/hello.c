#include "types.h"
#include "stat.h"
#include "user.h"

#define STDIN 0
#define STDOUT 1
#define STDERR 2

int main() {
    //trace(1);
    printf(STDOUT, "Hello World!\n");
    exit();
}