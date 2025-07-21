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
