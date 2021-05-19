#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/irq.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/arch/regs-gpio.h>
#include <asm/hardware.h>


static struct class *irq_button_drv_class;
static struct class_device	*irq_button_drv_class_dev;

//GPF端口
volatile unsigned long *gpfcon;
volatile unsigned long *gpfdat;

//GPG端口
volatile unsigned long *gpgcon;
volatile unsigned long *gpgdat;

//dev 就是request_irq的最后一个参数
static irqreturn_t buttons_irq(int irq, void *dev) 
{
    printk("irq = %d\n",irq);
    return 0;
}

static int irq_button_drv_open(struct inode * inode, struct file * file)
{
    // 配置GPF2,0为输入引脚  GPF2 = 00 GPF0 = 00
    // 配置GPG3,11为输入引脚  GPG3 = 00 GPG11 = 00
    // 中断源，中断处理函数，检测上升下降沿，中断设备名，...
	request_irq(IRQ_EINT0,  buttons_irq, IRQT_BOTHEDGE, "S2", 0);
	request_irq(IRQ_EINT2,  buttons_irq, IRQT_BOTHEDGE, "S3", 0);
	request_irq(IRQ_EINT11, buttons_irq, IRQT_BOTHEDGE, "S4", 0);
	request_irq(IRQ_EINT19, buttons_irq, IRQT_BOTHEDGE, "S5", 0);	
    printk("open irq\n");
    return 0;
}



ssize_t irq_button_drv_read(struct file *file, char __user *buf, size_t size, loff_t *ppos){
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

int irq_button_close (struct inode * inode, struct file * file) {
    //释放IRQ
    free_irq(IRQ_EINT0,0);
    free_irq(IRQ_EINT2,0);
    free_irq(IRQ_EINT11,0);
    free_irq(IRQ_EINT19,0);
    printk("free irq\n");
    return 0;
}

static struct file_operations button_drv_fops = {
    .owner  =   THIS_MODULE,   
    .open   =   irq_button_drv_open,     
	.read	=	irq_button_drv_read,
    .release =  irq_button_close,    
};




int major;
static int irq_button_drv_init(void)
{
    major = register_chrdev(0,"irq_button_drv", &button_drv_fops);

	irq_button_drv_class = class_create(THIS_MODULE, "irq_button_drv"); 
	irq_button_drv_class_dev = class_device_create(irq_button_drv_class, NULL, MKDEV(major, 0), NULL, "button"); /* /dev/xyz */

	gpfcon = (volatile unsigned long *)ioremap(0x56000050, 16);  //地址映射：从0x56000050开始的16个字节的内存映射到gpfcon
	gpfdat = gpfcon + 1;

 	gpgcon = (volatile unsigned long *)ioremap(0x56000060, 16);  //地址映射：从0x56000050开始的16个字节的内存映射到gpfcon
	gpgdat = gpgcon + 1;

    return 0;
}

static void irq_button_drv_exit(void)
{
    unregister_chrdev(major,"irq_button_drv");

	class_device_unregister(irq_button_drv_class_dev);
	class_destroy(irq_button_drv_class);

    iounmap(gpfcon);
    iounmap(gpgcon);
    return 0;
}



module_init(irq_button_drv_init);
module_exit(irq_button_drv_exit);
MODULE_LICENSE("GPL");
