#include <linux/module.h>

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>

#define DEVICENAME "myled"

static unsigned int major=0;
unsigned int pin=0;
static struct class *myclass=NULL;
static struct class_device  *mydev;

static volatile unsigned long *gpfcon=NULL;
static volatile unsigned long *gpfdat=NULL;

#define GPFCON *gpfcon
#define GPFDAT *gpfdat


static int led_open(struct inode *inode, struct file *file)
{
    //配置LED管脚模式
    GPFCON &=~(0x3<<(pin*2));
    GPFCON |= (0x1<<(pin*2));

    //默认灯全部关闭
    GPFDAT |= ((7<<4));
    return 0;
}

static ssize_t led_write(struct file *file, const char __user *buf, size_t count, loff_t * ppos)
{
    int val;

    copy_from_user(&val, buf, count); //    copy_to_user();

    if (val == 1)
    {
        // 点灯
        GPFDAT &= ~(1<<pin);
    }
    else
    {
        // 灭灯
        GPFDAT |= (1<<pin);
    }

    return 0;
}

static struct file_operations my_dev_fops = {
    .owner  =   THIS_MODULE,    /* 这是一个宏，推向编译模块时自动创建的__this_module变量 */
    .open   =   led_open,     
    .write  =   led_write,

};


/* 分配/设置/注册一个platform_driver */
static int __devinit led_probe(struct platform_device *pdev)
{
    /* 根据platform_dev资源进行ioremap */
    struct resource *res;
    // 从device中获取资源 resource led_resource[]
    // parms: device ,资源类型，资源索引
    res = platform_get_resource(pdev,IORESOURCE_MEM,0);
    gpfcon = ioremap(res->start,res->end-res->start+1);
    gpfdat= gpfcon+1;

    res=platform_get_resource(pdev,IORESOURCE_IRQ,0);
    pin=res->start;

    /* 注册字符设备   */
    major = register_chrdev(0,DEVICENAME, &my_dev_fops); // 注册, 告诉内核
    myclass = class_create(THIS_MODULE,DEVICENAME);
    mydev=device_create(myclass, NULL, MKDEV(major,0), NULL, "led");
    printk("led_probe,found led\n");
    return 0;
}

static int __devexit led_remove(struct platform_device *pdev)
{
    /* 根据platform_dev资源进行iounmap */
    /* 注销字符设备   */
    iounmap(gpfcon);


    device_unregister(mydev);
    class_destroy(myclass);
    unregister_chrdev(major, DEVICENAME); // 卸载
    printk("led_remove,remove led\n");
    return 0;
}

struct platform_driver led_drv = {
    .probe      = led_probe,  // 初始化
    .remove     = led_remove, // 卸载
    .driver     = {
        .name   = "myled",
    }
};

static int led_drv_init(void)
{
    platform_driver_register(&led_drv);
    return 0;
}

static void led_drv_exit(void)
{
    platform_driver_unregister(&led_drv);
}

module_init(led_drv_init);
module_exit(led_drv_exit);
MODULE_LICENSE("GPL");

