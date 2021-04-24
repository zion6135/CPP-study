# CPP-study
记录C++学习历程

2.Linux:
linux内核版本：linux-2.6.22.6
交叉编译工具链：arm-linux-gcc 3.4.5  使用教程：https://blog.csdn.net/m0_37844072/article/details/113729680第三点

led{ 教程： https://blog.csdn.net/m0_37844072/article/details/114107274  }

3.Socket-udp{教程：https://blog.csdn.net/m0_37844072/category_10988339.html?spm=1001.2014.3001.5482}
编译：进入socket-udp文件夹-->sudo cmake ./-->sudo make 
注意：需要保证为当前电脑的IP地址
客户端运行：./demo client
服务端运行：./demo xxx

添加了信号量和消息队列
4.json
//  1.创建json数据
//  2.cJSON结构体数据
//  3.转cJSON结构体为字符串
//  4.解析json字符串--> cJSON结构体  
//  5.解析cJSON结构体得到里面的内容
