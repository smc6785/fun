#include <linux/module.h>
#include <linux/init.h>
#include <linux/pci.h>

#define SMC6785_VENDOR_ID 0x6785
#define SMC6785_DEVICE_ID 0x6666

static struct pci_device_id smc6785_ids[] = {
  {SMC6785_VENDOR_ID, SMC6785_DEVICE_ID},
  {}
};

// To expose this table to userspace, like probe()
MODULE_DEVICE_TABLE(pci, smc6785_ids);

static int smc6785_probe(struct pci_dev *dev, const struct pci_device_id *id)
{
  u16 vid, did;
  u8 capability_ptr;
  u32 bar0, saved_bar0;

  pci_read_config_word(dev, 0x0, &vid);
  pci_read_config_word(dev, 0x2, &did);
  pci_read_config_word(dev, 0x34, &capability_ptr);
  pci_read_config_word(dev, 0x10, &bar0);

  saved_bar0 = bar0;

  // BAR0 could be in IO space and memory space.
  // Use BAR0 to calculate the size.
  // Use lspci -v to verivfy the size.

  pci_write_config_word(dev, 0x10, 0xFFFFFFFF);
  pci_read_config_word(dev, 0x10, &bar0);
  bar0 &= 0xFFFFFFFF;
  bar0 = ~bar0;
  bar0++;
  // bar0 is the size of bar0
  // bar0_size = pci_resouce_len(dev, 0);
  pci_write_config_word(dev, 0x10, &saved_bar0);

  pcim_enable_device(dev); 
  // BAR0 is mapped to pci_resouce_start(dev, 0)
  // pcim_iomap_regions(dev, BIT(0), KBUILD_MODNAME)
  // ptr_bar0 = pcim_iomap_table(dev)[0]
  // ioread32(ptr_bar0 + 0x6);
  // iowrite32(ptr_bar0 + 0x7);
#if 0
  // Set up interrupt from PCI device
  devm_request_irq(&dev->dewv, dev->irq, my_irq_handler, 0, KBUILD_MODNAME, my_data);

  bar = pci_select_cars(dev, IORESOURCE_MEM);
  pci_enable_device_mem(dev);
  pci_request_region(dev, bar, "smc6785");
  mmio_start = pci_resource_start(dev, 0); 
  mmio_len = pci_resource_len(dev, 0); 
  hwmem = ioremap(mmio_start, mmio_len);

#endif
  return 0;
}

static void smc6785_remove(struct pci_dev *dev)
{
}



static struct pci_driver smc6785_driver = {
  .name = "smc6785",
  .id_table = smc6785_ids,
  .probe = smc6785_probe,
  .remove = smc6785_remove,
};

static int __init init_hello(void)
{
    return pci_register_driver(&smc6785_driver);
}

static void __exit cleanup_hello(void)
{
    pci_unregister_driver(&smc6785_driver);
}

module_init(init_hello);
module_exit(cleanup_hello);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("smc6785");
MODULE_DESCRIPTION("A smc6785 pcie kernel driver. ");


#if 0
#include <linux/module.h> 
#include <linux/init.h> 
#include <linux/fs.h> 

int count = 1;
// sudo insmod hello.ko count=3
module_param(count, int, 0);
MODULE_PARM_DESC(count, "how many times we print hellowolrd");

static int major;

// file_operations is defined in
// https://github.com/torvalds/linux/blob/master/include/linux/fs.h
static ssize_t smc_read (struct file *f, char __user *u, size_t l, loff_t *o)
{
    printk(KERN_INFO "smc_read is called\n");
    return 0;
}

static struct file_operations fops = {
    .read = smc_read
};

static int __init init_hello(void)
{
    int i;
    for (i = 0; i < count; i++)
    {
        printk("hello world, count: %d \n", count);
    }

    // 0, linux will search a free device number
    //  and allocate 256 devices
    // smc6785_lable will be in /proc/devices
    major = register_chrdev(0, "smc6785_lable", &fops);
    if (major < 0){
        printk(" Error registering chrdev");
    }
    printk(KERN_ALERT "smc6785: registered a char device, major number : %d \n", major);
    return 0;
}

static void __exit cleanup_hello(void)
{
    unregister_chrdev(major, "smc6785_lable");
    printk(KERN_DEBUG "exit : hello world \n");
}

module_init(init_hello);
module_exit(cleanup_hello);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("smc6785 <smc6785@psu.edu>");
MODULE_DESCRIPTION("Register for a character device. ");
// modinfo hello.ko

#if 0
sudo dmesg | tail
sudo dmesg | tail -n 1 
sudo dmesg -W
sudo dmesg -w

sudo modprobe, will also install all dependencies.

cro------- 1 root    root     10, 231 Jul 15 15:13 snapshot
c,ocharacter device file
write or reade bytes
10, major device numer 
231, minor device wumber

brw-rw---- 1 root    disk    253,   0 Jul 15 15:13 dm-0
b, block device file
wrtie or read a block

ls -l /dev/tty{1,2,3,4,5}
cat /proc/devices
sudo hexdump dm-0 | head

sudo mknod smc6785 b 179 0
sudo mknod myserial c 4 64
ls -l smc6785

sudo mknod smc c 238 0 
sudo mknod smc128 c 238 128
vagrant@vagrant:/dev$ sudo cat /dev/smc 
vagrant@vagrant:/dev$ sudo cat /dev/smc128
cat: /dev/smc: Invalid argument
Need to implement read function on this device.
dmesg: [ 5209.001317] smc_read is called

./linux-5.15.0/scripts/checkpatch.pl ../fun/os/kernel_module/hello.c 
cat /proc/sys/kernel/printk

https://www.youtube.com/watch?v=_TmZ7cACfn0
sudo demsg -l 7

/etc/apt/sources.list
sudo apt-get install linux-headers-$(uname -r)
/usr/src/linux-headers-5.15.0-133-generic$


#endif

#endif