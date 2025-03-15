#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>

#define CHILD_LOG_INDENT 10

void find_process(pid_t);
void log_memory_map(struct mm_struct *, char *indent_str);

int pid_int;
module_param(pid_int, int, 0);

static int module_load(void) {
  pr_info("Loading mem_module!\n");

  find_process((pid_t)pid_int);
  return 0;
}

static void module_unload(void) { pr_info("\nUnloading mem_module!\n"); }

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
      pr_info("Memory map of parent process with PID = %d\n", pid);
      struct mm_struct *mm = task->mm;
      log_memory_map(mm, "|--");

      char child_header_indent_str[CHILD_LOG_INDENT + 1 + 1];
      child_header_indent_str[0] = '|';
      for (int i = 1; i < CHILD_LOG_INDENT; i++) {
        child_header_indent_str[i] = '-';
      }
      child_header_indent_str[CHILD_LOG_INDENT] = '\0';

      char child_logs_indent_str[CHILD_LOG_INDENT + 1 + 1];
      child_logs_indent_str[0] = '|';
      for (int i = 1; i < CHILD_LOG_INDENT - 3; i++) {
        child_logs_indent_str[i] = ' ';
      }
      child_logs_indent_str[CHILD_LOG_INDENT - 3] = '|';
      child_logs_indent_str[CHILD_LOG_INDENT - 2] = '-';
      child_logs_indent_str[CHILD_LOG_INDENT - 1] = '-';
      child_logs_indent_str[CHILD_LOG_INDENT] = '\0';

      struct task_struct *child;
      rcu_read_lock();

      list_for_each_entry_rcu(child, &task->children, sibling) {
        pr_info("|\n");

        if (child->sibling.next == &task->children) {
          child_logs_indent_str[0] = ' ';
        }

        pr_info("%s Memory map of child process with PID = %d\n",
                child_header_indent_str, child->pid);
        struct mm_struct *child_mm = child->mm;
        log_memory_map(child_mm, child_logs_indent_str);
      }
    }
  }

  if (!valid_pid) {
    pr_info("Process with PID = %d not found!\n", pid);
  }
}

void log_memory_map(struct mm_struct *mm, char *indent_str) {
  if (mm) {
    mmap_read_lock(mm);

    VMA_ITERATOR(vma_iter, mm, 0);
    vma_iter_init(&vma_iter, mm, 0);

    struct vm_area_struct *vma;
    for_each_vma(vma_iter, vma) {
      static char *vma_type;

      if (vma->vm_start <= vma->vm_mm->start_stack &&
          vma->vm_end >= vma->vm_mm->start_stack) {
        vma_type = "[stack]";
      } else if (vma->vm_file) {
        vma_type = vma->vm_file->f_path.dentry->d_name.name;
      } else if (vma->vm_start < mm->brk &&
                 vma->vm_end > vma->vm_mm->start_brk) {
        vma_type = "[heap]";
      } else {
        vma_type = "[unknown]";
      }
      pr_info("%s VMA start = 0x%lx, end = 0x%lx, size = %lu KB, flags = "
              "0x%lx, segment/file path = %s",
              indent_str, vma->vm_start, vma->vm_end,
              (vma->vm_end - vma->vm_start) / 1024, vma->vm_flags, vma_type);
    }

    pr_info("%s Total memory segment count = %d\n", indent_str, mm->map_count);
    mmap_read_unlock(mm);
  } else {
    pr_info("%s task->mm is NULL (Kernel thread)\n", indent_str);
    return;
  }
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anirudh Sudhir");
MODULE_DESCRIPTION("Kernel module to display the memory map of a process and "
                   "all its children");
