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

static DECLARE_WAIT_QUEUE_HEAD(button_waitq);

struct pin_desc{
    unsigned int pin;
    unsigned int key_val;
};

//自定义：按下key_val = 0x01, 0x02, 0x03, 0x04
//自定义：松开key_val = 0x81, 0x82, 0x83, 0x84
static unsigned char key_val;

struct pin_desc pins_desc[4] = {
	{S3C2410_GPF0, 0x01},
	{S3C2410_GPF2, 0x02},
	{S3C2410_GPG3, 0x03},
	{S3C2410_GPG11, 0x04},
};


static volatile int ev_press = 0;

//dev 就是request_irq的最后一个参数
//irq 就是request_irq的第一个参数 
static irqreturn_t buttons_irq(int irq, void *dev) 
{
    printk("irq = %d\n",irq);
    struct pin_desc* pindesc = (struct pin_desc*)dev;
    unsigned int pinval;

    pinval = s3c2410_gpio_getpin(pindesc->pin);
    if (pinval) { // 松开
        key_val = 0x80 | pindesc->key_val;
    } else { // 按下
        key_val = pindesc->key_val;
    }

    ev_press = 1;                  /* 表示中断发生了 */
    wake_up_interruptible(&button_waitq);   /* 唤醒休眠的进程 */

    return 0;
}

static int irq_button_drv_open(struct inode * inode, struct file * file)
{
    // 配置GPF2,0为输入引脚  GPF2 = 00 GPF0 = 00
    // 配置GPG3,11为输入引脚  GPG3 = 00 GPG11 = 00
    // 中断源，中断处理函数，检测上升下降沿，中断设备名，...
	request_irq(IRQ_EINT0,  buttons_irq, IRQT_BOTHEDGE, "S2", &pins_desc[0]);
	request_irq(IRQ_EINT2,  buttons_irq, IRQT_BOTHEDGE, "S3", &pins_desc[1]);
	request_irq(IRQ_EINT11, buttons_irq, IRQT_BOTHEDGE, "S4", &pins_desc[2]);
	request_irq(IRQ_EINT19, buttons_irq, IRQT_BOTHEDGE, "S5", &pins_desc[3]);	
    printk("open irq\n");
    return 0;
}



ssize_t irq_button_drv_read(struct file *file, char __user *buf, size_t size, loff_t *ppos){

    // 如果没有按键动作，则休眠
	wait_event_interruptible(button_waitq, ev_press); // 阻塞等待

    // 如果有按键动作，返回键值
    copy_to_user(buf,&key_val,1);
    ev_press = 0;
    return 1;
}

int irq_button_close (struct inode * inode, struct file * file) {
    //释放IRQ
    free_irq(IRQ_EINT0,&pins_desc[0]);
    free_irq(IRQ_EINT2,&pins_desc[1]);
    free_irq(IRQ_EINT11,&pins_desc[2]);
    free_irq(IRQ_EINT19,&pins_desc[3]);
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
