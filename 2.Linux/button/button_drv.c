#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/arch/regs-gpio.h>
#include <asm/hardware.h>
 
static struct class *buttondrv_class;
static struct class_device	*buttondrv_class_dev;

//GPF端口
volatile unsigned long *gpfcon;
volatile unsigned long *gpfdat;

//GPG端口
volatile unsigned long *gpgcon;
volatile unsigned long *gpgdat;

static int button_drv_open(struct inode * inode, struct file * file)
{
    // 配置GPF2,0为输入引脚  GPF2 = 00 GPF0 = 00
    *gpfcon &= ~((0x03<<(0*2)) | (0x3<<(2*2)));
    // 配置GPG3,11为输入引脚  GPG3 = 00 GPG11 = 00
    *gpgcon &= ~((0x03<<(3*2)) | (0x3<<(11*2)));

    return 0;
}

ssize_t button_drv_read(struct file *file, char __user *buf, size_t size, loff_t *ppos){
    //返回四个引脚电平
    unsigned char key_val[4];
    int ret_val;


    //读取GPF0 2
    ret_val = *gpfdat;
    key_val[0] = (ret_val & (1 << 0)) ? 1:0;
    key_val[1] = (ret_val & (1 << 2)) ? 1:0;

    //读取GPG3 11
    ret_val = *gpgdat;
    key_val[2] = (ret_val & (1 << 3)) ? 1:0;
    key_val[3] = (ret_val & (1 << 11)) ? 1:0;

    copy_to_user(buf,key_val,sizeof(key_val));
    return sizeof(key_val);
}

static struct file_operations button_drv_fops = {
    .owner  =   THIS_MODULE,   
    .open   =   button_drv_open,     
	.read	=	button_drv_read,	   
};




int major;
static int button_drv_init(void)
{
    major = register_chrdev(0,"button_drv", &button_drv_fops);

	buttondrv_class = class_create(THIS_MODULE, "button_drv"); 
	buttondrv_class_dev = class_device_create(buttondrv_class, NULL, MKDEV(major, 0), NULL, "button"); /* /dev/xyz */

	gpfcon = (volatile unsigned long *)ioremap(0x56000050, 16);  //地址映射：从0x56000050开始的16个字节的内存映射到gpfcon
	gpfdat = gpfcon + 1;

 	gpgcon = (volatile unsigned long *)ioremap(0x56000060, 16);  //地址映射：从0x56000050开始的16个字节的内存映射到gpfcon
	gpgdat = gpgcon + 1;

    return 0;
}

static void button_drv_exit(void)
{
    unregister_chrdev(major,"button_drv");

	class_device_unregister(buttondrv_class_dev);
	class_destroy(buttondrv_class);

    iounmap(gpfcon);
    iounmap(gpgcon);
    return 0;
}



module_init(button_drv_init);
module_exit(button_drv_exit);
MODULE_LICENSE("GPL");
