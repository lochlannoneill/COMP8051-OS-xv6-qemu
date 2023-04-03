#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "uproc.h"
#include "spinlock.h"

int sys_fork(void)
{
  return fork();
}

int sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int sys_wait(void)
{
  return wait();
}

int sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int sys_getpid(void)
{
  return myproc()->pid;
}

int sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int sys_trace(void)
{
  int enabled;

  if(argint(0, &enabled) < 0)
    return -1;

  myproc()->trace_enabled = enabled;

  if(enabled == 1) {
    struct proc *p = myproc();
    myproc()->syscall_count++;
    cprintf("pid: %d [%s] syscall(%d=%s)\n", p->pid, p->name, p->tf->eax, "syscall_name");
    //cprintf("pid: %d [%s] syscall(%d=%s)\n", p->pid, p->name, p->tf->eax, syscallnames[p->tf->eax]);
  }

  return myproc()->syscall_count;
}

// struct proc *getptable_proc(void);
extern int getprocs(int max, struct uproc *table);
int sys_getprocs(void)
{
  int max;
  struct uproc *table;

  if(argint(0, &max) < 0 || argptr(1, (char **)&table, max * sizeof(struct uproc)) < 0)
    return -1;

  return getprocs(max, table);
}