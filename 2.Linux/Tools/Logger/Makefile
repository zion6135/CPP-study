########################Makefile##########################
KERN_DIR = /home/zion/gcc_jz2440/linux-2.6.22.6  #这里一定要改为与代码匹配的内核的路径，否则会有各种问题
 
all:
	make -C $(KERN_DIR) M=`pwd` modules 
 
clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm -rf modules.order

obj-m	+= Logger2.o #名字要与button_drv.c匹配