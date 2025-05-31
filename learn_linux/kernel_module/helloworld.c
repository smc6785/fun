#include <linux/module.h> 

int count = 1;
module_param(count, int, 0);
MODULE_PARM_DESC(count, "how many times we print hellowolrd");

static int __init init_hello(void)
{
    int i;
    for (i = 0; i < count; i++)
    {
        printk("hello world \n");
    }
    return 0;
}

static void __exit cleanup_hello(void)
{
    printk("exit : hello world \n");
}

module_init(init_hello);
module_exit(cleanup_hello);
MODULE_LICENSE("GPL");

