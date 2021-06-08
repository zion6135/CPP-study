//linux 内核调试(dump_stack查看函数调用堆栈)
// PC：编译sudo make
// jz2440: 1.insmod Logger.ko 2.dmesg 3.rmmod Logger.ko
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kprobes.h>
#include <asm/traps.h>
 
MODULE_LICENSE("Dual BSD/GPL");
  
static int __init hello_init(void)
{
     printk(KERN_ALERT "dump_stack start\n");
     dump_stack();
     printk(KERN_ALERT "dump_stack over\n");
     return 0;
 }
 static void __exit hello_exit(void)
 {
      printk(KERN_ALERT "test module\n");
 }
 
module_init(hello_init);
module_exit(hello_exit);

