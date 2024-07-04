#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>

MODULE_AUTHOR("Evgeny Darichev");
MODULE_DESCRIPTION("My kernel module");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");

static char *p;

struct mydata {
    u64 value;
};

static struct mydata *pdata;

#define MY_BUF_SIZE 1024

static int __init mymodule_init(void)
{
    printk(KERN_INFO "Initializing MyModule...");
    p = kmalloc(MY_BUF_SIZE, GFP_KERNEL);
    if (!p) {
        WARN_ONCE(1, "%s: kmalloc failed\n", "MyModule");
        return -ENOMEM;
    }
    memset(p, 0xCC, MY_BUF_SIZE);
    pdata = kzalloc(sizeof(struct mydata), GFP_KERNEL);
    if (!pdata) {
        kfree(p);
        return -ENOMEM;
    }
    return 0;
}

static void __exit mymodule_exit(void)
{
    kfree(p);
    kfree(pdata);
    printk(KERN_INFO "Exit from MyModule");
}

module_init(mymodule_init);
module_exit(mymodule_exit);

