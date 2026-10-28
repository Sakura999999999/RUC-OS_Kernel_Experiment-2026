#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/types.h>
#include <linux/sched/signal.h>
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/mman.h>

/* 模块参数：指定目标 PID（-1 表示所有进程） */
static int pid = -1;
module_param(pid, int, 0644);
MODULE_PARM_DESC(pid, "Target PID (-1 for all processes)");

// 初始化模块
static int __init traverse_all_vma_init(void)
{
    struct task_struct *task;
    struct vm_area_struct *vma;

    // 遍历系统中所有进程
    for_each_process(task) {
        struct mm_struct *mm = task->mm;

        // 如果进程没有 mm（例如内核线程），则跳过
        if (!mm)
            continue;

        // 若设置了 pid 参数，则仅处理该 PID
        if (pid != -1 && task->pid != pid)
            continue;

        pr_info("Process %d (%s):\n", task->pid, task->comm);

        // 加锁与迭代
        mmap_write_lock(mm);

        // 遍历所有 VMA，切换 VM_WRITE 位并打印差异
        for (vma = mm->mmap; vma != NULL; vma = vma->vm_next) {
            unsigned long old_flags = vma->vm_flags;
            unsigned long new_flags; /* 仅用于打印/预期 */

            if (old_flags & (VM_IO | VM_PFNMAP))
                continue;

            if (old_flags & VM_SPECIAL)
                continue;

            // TODO: flip vma's WRITE flag

            new_flags = vma->vm_flags; /* 实际修改后的值 */

            pr_info("    flags before=0x%lx, after=0x%lx, diff=0x%lx\n",
                    old_flags, new_flags, old_flags ^ new_flags);
        }

        // 释放锁
        mmap_write_unlock(mm);
    }

    return 0;
}

// 卸载模块
static void __exit traverse_all_vma_exit(void)
{
    pr_info("Module unloaded: traverse all VMA.\n");
}

module_init(traverse_all_vma_init);
module_exit(traverse_all_vma_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("YourName");
MODULE_DESCRIPTION("Traverse virtual address space of all processes using kernel module");
