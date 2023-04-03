#include "types.h"
#include "stat.h"
#include "user.h"
#include "uproc.h"

int
main(int argc, char *argv[])
{
  struct uproc ptable[64];
  int n = getprocs(64, ptable);

  printf(1, "PID\tPPID\tSTATE\tSIZE\tNAME\n");
  for(int i = 0; i < n; i++) {
    printf(1, "%d\t%d\t%d\t%d\t%s\n", ptable[i].pid, ptable[i].ppid, ptable[i].state, ptable[i].sz, ptable[i].name);
  }

  exit();
}