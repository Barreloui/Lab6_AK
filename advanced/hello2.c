// SPDX-License-Identifier: GPL-2.0+

#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/moduleparam.h>
#include <linux/errno.h>

#include "hello1.h"

extern int print_hello(uint);

static uint n = 1;
module_param(n, uint, 0660);
MODULE_PARM_DESC(n, "A parameter that determines the number of messages. Recommended values: 1-5; unwanted values: 0, 6-10; invalid values: >10, <0;");

static int __init hello2_init(void)
{
	return print_hello(n);
}

static void __exit hello2_exit(void)
{
	/* Do nothing here right now */
}

module_init(hello2_init);
module_exit(hello2_exit);

MODULE_AUTHOR("Max Afanasiev <max_afanasiev@example.cpm>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training. Advanced, module 2.");
MODULE_LICENSE("Dual BSD/GPL");
