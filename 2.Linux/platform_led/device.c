#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/mtd/mtd.h>

#include <linux/mtd/partitions.h>
#include <linux/input.h>

#include <linux/module.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <asm/mach/flash.h>
#include <asm/mach/map.h>



#include <linux/fs.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>



/* 分配/设置/注册一个platform_device */

void led_release(struct device *dev)
{
    printk("led device release\r\n");

}
static struct resource led_resource[] = {

    [0]=
    {
        .start      = 0x56000050,
        .end        = 0x56000050 + 8 - 1,
        .flags      = IORESOURCE_MEM,
    },
    [1]=
    {
        .start      = 4,
        .end        = 4,
        .flags      = IORESOURCE_IRQ,
    }
};



static struct platform_device led_dev = {
    .name       = "myled",
    .id     = -1,  // 无此设备
    .dev        = {
        .release = led_release,
    },
    // 资源数量
    .num_resources  = ARRAY_SIZE(led_resource),
    
    .resource   = led_resource,
};


static int led_dev_init(void)
{
    platform_device_register(&led_dev);
    return 0;
}

static void led_dev_exit(void)
{
    platform_device_unregister(&led_dev);
}
module_init(led_dev_init);
module_exit(led_dev_exit);
MODULE_LICENSE("GPL");

