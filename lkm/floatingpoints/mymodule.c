/* Как использовать floating point в kernel mode */

/* Вывод:
 * $ make
 * $ sudo insmod mymodule.ko
 * $ sudo dmesg
 * [ 1064.066819] Initializing MyModule...
 * [ 1064.066828] Double value: 123.450
 * $ sudo rmmod mymodule.ko
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <asm/fpu/api.h>



MODULE_AUTHOR("Evgeny Darichev");
MODULE_DESCRIPTION("My kernel module");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");


static int __init mymodule_init(void)
{
    double dv;
    int hi, lo;
    printk(KERN_INFO "Initializing MyModule...");
    
    kernel_fpu_begin();
    /* далее можно использовать double, float... */
    dv = 123.45;
#ifdef THIS_IS_AN_ERROR
    pr_info("Double value: %g\n", dv); /* так не сработает: %f, %g не распознаются*/
#endif
    // просто режем число, в простейшем случае так:
    hi = (int)dv;
    dv -= hi;
    dv *= 1000; // 3 знака после запятой, *10^3
    lo = (int)dv;
    pr_info("Double value: %d.%d\n", hi, lo);
    kernel_fpu_end(); /* отключить поддержку fp */
    return 0;
}

static void __exit mymodule_exit(void)
{
    printk(KERN_INFO "Exit from MyModule");
}

module_init(mymodule_init);
module_exit(mymodule_exit);

