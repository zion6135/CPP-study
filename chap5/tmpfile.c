/************临时文件 5.13*************/
// 1.不冲突--并发操作 2.及时销毁
//创建临时文件
// tmpnam()
// tmpfile() --->创建一个匿名文件： ls 也看不到--->如果程序正常终止，会自动删除此文件
