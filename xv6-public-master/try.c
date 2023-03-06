#include "types.h"
#include "stat.h"
#include "user.h"

#define STDIN 0
#define STDOUT 1
#define STDERR 2

int main(int argc, char *argv[]) {
  printf(STDOUT, "Currently running 'try.c'\n");
  int count_syscalls;

  count_syscalls = trace(0); //should == 0
  printf(STDOUT, "trace(0) -> total system calls so far = %d\n", count_syscalls); // should print the total number of system calls made by the process

  count_syscalls = trace(1); //should == 1
  printf(STDOUT, "trace(1) -> total system calls so far = %d\n", count_syscalls); // should print the total number of system calls made by the process

  count_syscalls = trace(0); //should still == 1
  printf(STDOUT, "trace(0) -> total system calls so far = %d\n", count_syscalls); // should print the total number of system calls made by the process

  count_syscalls = trace(1); //should == 2
  printf(STDOUT, "trace(1) -> total system calls so far = %d\n", count_syscalls); // should print the total number of system calls made by the process


  exit();
}

