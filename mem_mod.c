#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>

void find_process(pid_t);
void log_memory_map(struct mm_struct *);

int pid_int;
module_param(pid_int, int, 0);

static int module_load(void) {
  pr_info("Loading mem_module!\n");

  find_process((pid_t)pid_int);
  return 0;
}

static void module_unload(void) { pr_info("Unloading mem_module!\n"); }

module_init(module_load);
module_exit(module_unload);

void find_process(pid_t pid) {
  struct task_struct *task;
  bool valid_pid = false;
  for_each_process(task) {

    if (task->pid == pid) {
      valid_pid = true;

      pr_info("Found parent process with PID = %d, Name = %s\n", pid,
              task->comm);
      pr_info("Displaying memory map of the parent process with PID = %d\n",
              pid);
      struct mm_struct *mm = task->mm;
      log_memory_map(mm);

      pr_info("Iterating through child process\n");
      struct task_struct *child;
      rcu_read_lock();

      list_for_each_entry_rcu(child, &task->children, sibling) {
        pr_info("\n");
        pr_info("Found child process with PID = %d\n", child->pid);
        struct mm_struct *child_mm = child->mm;
        log_memory_map(child_mm);
      }
      pr_info("\n");
    }
  }

  if (!valid_pid) {
    pr_info("Process with PID = %d not found!\n", pid);
  }
}

void log_memory_map(struct mm_struct *mm) {
  if (mm) {
    mmap_read_lock(mm);

    struct vm_area_struct *vma;
    VMA_ITERATOR(vma_iter, mm, 0);
    vma_iter_init(&vma_iter, mm, 0);

    for_each_vma(vma_iter, vma) {
      static char *vma_type;
      if (vma->vm_flags & VM_STACK) {
        vma_type = "[stack]";
      } else if (vma->vm_file) {
        vma_type = vma->vm_file->f_path.dentry->d_name.name;
      } else if (vma->vm_start >= mm->start_brk && vma->vm_end <= mm->brk) {
        vma_type = "[heap]";
      } else {
        vma_type = "[unknown]";
      }
      pr_info("VMA start = 0x%lx, end = 0x%lx, size = %lu, flags = "
              "0x%lx, segment/file path = %s",
              vma->vm_start, vma->vm_end, (vma->vm_end - vma->vm_start),
              vma->vm_flags, vma_type);
    }

    pr_info("Total memory segment count = %d\n", mm->map_count);
    mmap_read_unlock(mm);
  } else {
    pr_info("task->mm is NULL (Kernel thread)\n");
    return;
  }
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anirudh Sudhir");
MODULE_DESCRIPTION("Kernel module to display the memory map of a process and "
                   "all its children");
