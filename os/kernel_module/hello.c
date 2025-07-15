#include <linux/module.h> 
#include <linux/init.h> 

int count = 1;
// module_param(count, int, 0);
// MODULE_PARM_DESC(count, "how many times we print hellowolrd");

static int init_hello(void)
{
    int i;
    for (i = 0; i < count; i++)
    {
        printk("hello world \n");
    }
    return 0;
}

static void cleanup_hello(void)
{
    printk("exit : hello world \n");
}

module_init(init_hello);
module_exit(cleanup_hello);
MODULE_LICENSE("GPL");

