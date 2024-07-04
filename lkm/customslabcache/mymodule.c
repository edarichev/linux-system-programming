#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>

MODULE_AUTHOR("Evgeny Darichev");
MODULE_DESCRIPTION("My kernel module");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");

#define CACHE_NAME "mycache"

struct mystruct
{
    char mydata[234];
};

static struct kmem_cache *pCache;

// Подобие конструктора
// pMemory - выделенная память, заполним её чем-нибудь.
void fn_ctor(void *pMemory)
{
    struct mystruct *context = pMemory;
    pr_info("Constructor: address = 0x%llx\n", (long long unsigned int)context);
    memset(context, 0, sizeof(struct mystruct));
}

static int create_cache(void)
{
    void *pFnConstructor = fn_ctor;
    pCache = kmem_cache_create(CACHE_NAME, 
        sizeof(struct mystruct),// минимальный размер каждого объекта
        sizeof(long),           // выравнивание
        SLAB_POISON | SLAB_RED_ZONE | SLAB_HWCACHE_ALIGN,
        pFnConstructor);
    if (!pCache)
        return -ENOMEM;
    return 0;
}

static int __init mymodule_init(void)
{
    struct myctx *obj = NULL;
    printk(KERN_INFO "Initializing MyModule...");
    create_cache();
    obj = kmem_cache_alloc(pCache, GFP_KERNEL);
	if (!obj) {		/* pedantic warning printk below... */
		pr_warn("[Pedantic] kmem_cache_alloc() failed\n");
		return -ENOMEM;
	}

	pr_info("Our cache object (@ %pK, actual=%px) size is %u bytes; actual ksize=%zu\n",
		obj, obj, kmem_cache_size(pCache), ksize(obj));
	print_hex_dump_bytes("obj: ", DUMP_PREFIX_OFFSET, obj, sizeof(struct mystruct));

	/* free it */
	kmem_cache_free(pCache, obj);
    return 0;
}

static void __exit mymodule_exit(void)
{
    kmem_cache_destroy(pCache);
    printk(KERN_INFO "Exit from MyModule");
}

module_init(mymodule_init);
module_exit(mymodule_exit);

