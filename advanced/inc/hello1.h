#ifndef HELLO1_H
#define HELLO1_H

#include <linux/list.h>

struct data {
	ktime_t time_before;
	ktime_t	time_after;
	struct list_head list;
};

int print_hello(uint);

#endif
