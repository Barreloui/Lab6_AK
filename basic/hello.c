// SPDX-License-Identifier: GPL-2.0+

#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/moduleparam.h>
#include <linux/errno.h>
#include <linux/ktime.h>
#include <linux/list.h>
#include <linux/slab.h>

static uint n = 1;
module_param(n, uint, 0660);
MODULE_PARM_DESC(n, "A parameter that determines how many times the message will be displayed. Accepts values from 0-10.");

struct data {
	ktime_t time;
	struct list_head list;
};

struct list_head *iter, *iter_safe;
struct data *item;
LIST_HEAD(list);

static int __init hello_init(void)
{
	int i;

	pr_alert("Parameter values: %u", n);
	if (n <= 10) {
		if (n == 0)
			pr_warn("Warning: low parameter value!\n");
		else if (n > 5)
			pr_warn("Warning: values in the range 6-10 are undesirable!\n");

		for (i = 0; i < n; i++) {
			item = kmalloc(sizeof(*item), GFP_KERNEL);
			item->time = ktime_get_ns();
			list_add_tail(&(item->list), &list);
			pr_alert("Hello, world!\n");
		}
	} else {
		pr_err("Error: parameter value is greater than 10!\n");
		return -EINVAL;
	}
	return 0;
}

static void __exit hello_exit(void)
{
	list_for_each_safe(iter, iter_safe, &list) {
		item = list_entry(iter, struct data, list);
		pr_info("Processor time: %lu\n", (unsigned long) item->time);
		list_del(iter);
		kfree(item);
	}
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("Max Afanasiev <max_afanasiev@example.cpm>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");
