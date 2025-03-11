#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/printk.h>

static int __init module_load(void) {
  pr_info("Loading mem_module!\n");
  return 0;
}

static void __exit module_unload(void) { pr_info("Unloading mem_module!\n"); }

module_init(module_load);
module_exit(module_unload);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anirudh");
MODULE_DESCRIPTION("Kernel module to display the memory map of a process and "
                   "all its children");
