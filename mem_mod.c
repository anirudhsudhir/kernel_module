#include <linux/init.h>
#include <linux/kernel.h>
// for kernerl modules
#include <linux/module.h>
// pr_info
#include <linux/moduleparam.h>
#include <linux/printk.h>

int pid_int;
module_param(pid_int, int, 0);

static int module_load(void) {
  pr_info("Loading mem_module!\n");
  pr_info("PID to trace: %d\n", pid_int);
  return 0;
}

static void module_unload(void) { pr_info("Unloading mem_module!\n"); }

module_init(module_load);
module_exit(module_unload);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anirudh Sudhir");
MODULE_DESCRIPTION("Kernel module to display the memory map of a process and "
                   "all its children");
