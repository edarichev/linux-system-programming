#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/cred.h>
#include <linux/uidgid.h>

MODULE_AUTHOR("Evgeny Darichev");
MODULE_DESCRIPTION("My kernel module");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");

static void show_context(void)
{
    unsigned int uid = from_kuid(&init_user_ns, current_uid());
	unsigned int euid = from_kuid(&init_user_ns, current_euid());
    
    if (likely(in_task())) {
        printk(KERN_INFO "PID: %10d\nUID: %10d\nEUID:%10d\n", 
            task_pid_nr(current), // вместо current->pid
            uid, euid);
    }
}

static int __init mymodule_init(void)
{
    printk(KERN_INFO "Initializing MyModule...");
    show_context();
    return 0;
}

static void __exit mymodule_exit(void)
{
    printk(KERN_INFO "Exit from MyModule");
}

module_init(mymodule_init);
module_exit(mymodule_exit);

