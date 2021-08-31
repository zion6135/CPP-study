########################Makefile##########################
KERN_DIR =/home/zion/Desktop/JZ2440+QT/linux-3.4.2/linux-3.4.2  #这里一定要改为与代码匹配的内核的路径，否则会有各种问题
 
all:
	make -C $(KERN_DIR) M=`pwd` modules 
 
clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm -rf modules.order

obj-m	+= driver.o device.o#名字要与led_drv.c匹配
