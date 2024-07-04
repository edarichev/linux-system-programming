#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

void show_sysinfo(void)
{
    char msgBuf[256];
    memset(msgBuf, 0, sizeof(msgBuf));
    snprintf(msgBuf, 255, "MyModule, system info: ");
#ifdef CONFIG_X86
#   if (BITS_PER_LONG == 32)
    strncat(msgBuf, "32 bit", 7);
#   elif (BITS_PER_LONG == 64)
    strncat(msgBuf, "64 bit", 7);
#   endif
#endif // CONFIG_X86
    pr_info("%s\n", msgBuf);
}

EXPORT_SYMBOL(show_sysinfo);
