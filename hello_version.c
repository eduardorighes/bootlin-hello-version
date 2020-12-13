// SPDX-License-Identifier: GPL-2.0
#include <linux/init.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/utsname.h>
#include <linux/timekeeping.h>

static char *who = "World";
module_param(who, charp, 0644);
MODULE_PARM_DESC(who, "Who whould I greet?");

static time64_t load_time;

static int __init hello_init(void)
{
	load_time = ktime_get_real_seconds();
	pr_alert("Hello %s. This is Linux %s.\n", who, init_uts_ns.name.release);
	return 0;
}

static void __exit hello_exit(void)
{
	pr_alert("Goodbye %s. I was alive for %lld seconds.\n", who, ktime_get_real_seconds()-load_time);
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Eduardo Maestri Righes");
MODULE_DESCRIPTION("Dummy hello module");

