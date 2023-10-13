#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_AUTHOR("Evgeny Darichev");
MODULE_DESCRIPTION("My kernel module");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");

static int my_param;
module_param(my_param, int, 0660);
MODULE_PARM_DESC(my_param, "Default value is 12");

static int __init mymodule_init(void)
{
    printk(KERN_INFO "Initializing MyModule...");
    pr_info("Parameter passed: %d\n", my_param);
    if (my_param < 12) /* пусть это неправильное значение*/
        return -EINVAL; /*тогда получим: insmod: ERROR: could not insert module mymodule.ko: Invalid parameters*/
    return 0;
}

static void __exit mymodule_exit(void)
{
    printk(KERN_INFO "Exit from MyModule");
}

module_init(mymodule_init);
module_exit(mymodule_exit);

