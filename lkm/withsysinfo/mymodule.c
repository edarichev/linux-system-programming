/* Модуль со сбором информации о системе */
/*
 * Здесь два файла, поэтому либо делаем 2 модуля в Makefile:
SRCS   = mymodule.c showsysinfo.c
OBJS   = $(SRCS:.c=.o)
obj-m += $(OBJS)
 * и в таком порядке:
 * sudo insmod showsysinfo.ko
 * sudo insmod mymodule.ko
 * 
 * либо собираем в один так:
obj-m := mymodule.o
mymodule-objs := showsysinfo.o
 * (важно := вместо += )
 */
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_AUTHOR("Evgeny Darichev");
MODULE_DESCRIPTION("My kernel module");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");

void show_sysinfo(void);

static int __init mymodule_init(void)
{
    printk(KERN_INFO "Initializing MyModule...");
    show_sysinfo();
    return 0;
}

static void __exit mymodule_exit(void)
{
    printk(KERN_INFO "Exit from MyModule");
}

module_init(mymodule_init);
module_exit(mymodule_exit);

