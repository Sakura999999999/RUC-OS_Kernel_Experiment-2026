// SPDX-License-Identifier: GPL-2.0
#include <linux/module.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/mmzone.h>
#include <linux/mm_types.h>
#include <linux/sched/mm.h>
#include <linux/sched/signal.h>
#include <linux/page_ref.h>
#include <linux/gfp.h>
#include <linux/memblock.h>
#include <linux/highmem.h>
#include <linux/kernel.h>
#include <linux/sysinfo.h>
#include <linux/nodemask.h>
#include <linux/fs.h>
#include <linux/pgtable.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CheUhxg");
MODULE_DESCRIPTION("Show memory statistics and process memory map");
MODULE_VERSION("2.0");

static int pid = -1;
module_param(pid, int, 0644);
MODULE_PARM_DESC(pid, "Target process PID");

static void traverse_all_pages(void)
{
    unsigned long total_pages = 0;
    unsigned long valid_pages = 0;
    unsigned long free_pages = 0;
    unsigned long anon_pages = 0;
    unsigned long file_pages = 0;
    unsigned long slab_pages = 0;
    unsigned long dirty_pages = 0;
    unsigned long writeback_pages = 0;
    unsigned long lru_pages = 0;
    int nid;

    pr_info("[memory_status] ===== Page Frame Traversal =====\n");

    for_each_online_node(nid) {
        unsigned long start_pfn = node_start_pfn(nid);
        unsigned long end_pfn   = node_end_pfn(nid);
        unsigned long pfn;

        for (pfn = start_pfn; pfn < end_pfn; pfn++) {
            struct page *page;

            total_pages++;

            if (!pfn_valid(pfn))
                continue;

            valid_pages++;
            page = pfn_to_page(pfn);

            /* TODO: classify page and update relevant counters */
        }
    }

    pr_info("[memory_status] ===== Page Type Summary =====\n");
    pr_info("[memory_status] total_pfn         = %lu\n", total_pages);
    pr_info("[memory_status] valid_pfn         = %lu\n", valid_pages);
    pr_info("[memory_status] free_pages        = %lu\n", free_pages);
    pr_info("[memory_status] anon_pages        = %lu\n", anon_pages);
    pr_info("[memory_status] file_pages        = %lu\n", file_pages);
    pr_info("[memory_status] slab_pages        = %lu\n", slab_pages);
    pr_info("[memory_status] dirty_pages       = %lu\n", dirty_pages);
    pr_info("[memory_status] writeback_pages   = %lu\n", writeback_pages);
    pr_info("[memory_status] lru_pages         = %lu\n", lru_pages);
    pr_info("[memory_status] PAGE_SIZE         = %lu bytes\n", PAGE_SIZE);
}

static void show_vmas(struct mm_struct *mm)
{
    struct vm_area_struct *vma;

    pr_info("[memory_status] ===== Traverse VMA =====\n");

    /* TODO: iterate VMAs and print basic info */
}

static void traverse_page_table(struct mm_struct *mm)
{
    unsigned long addr;
    unsigned long mapped_pages = 0;
    const unsigned long end = mm->task_size;

    pr_info("[memory_status] ===== Page Table Walk (partial) =====\n");

    for (addr = 0; addr < end; addr += PAGE_SIZE) {
        /* TODO: walk the page table and count mapped pages
         * Reminder: use pte_offset_map() to access PTEs safely
         */
    }

    pr_info("[memory_status] Mapped pages: %lu\n", mapped_pages);
}

static int __init memory_status_init(void)
{
    struct task_struct *task;
    struct mm_struct *mm;

    traverse_all_pages();

    if (pid < 0) {
        return 0;
    }

    task = pid_task(find_vpid(pid), PIDTYPE_PID);

    if (!task) {
        pr_err("[memory_status] PID %d not found\n", pid);
        return -ESRCH;
    }

    mm = get_task_mm(task);
    if (!mm) {
        pr_err("[memory_status] PID %d has no mm_struct (kernel thread?)\n", pid);
        return -EINVAL;
    }

    pr_info("[memory_status] ===== Target process: %s (pid=%d) =====\n",
            task->comm, pid);

    show_vmas(mm);
    traverse_page_table(mm);

    mmput(mm);
    return 0;
}

static void __exit memory_status_exit(void)
{
    pr_info("[memory_status] Module unloaded.\n");
}

module_init(memory_status_init);
module_exit(memory_status_exit);
