//(1)栈。函数内的局部变量一般在这里创建，由编译器自动分配和释放。
//(2)堆。由程序员使用malloc/new申请，free/delete释放。
//(3)全局/静态存储区。全局变量和静态变量放这里，程序结束时释放。
//(4)常量存储区。存放常量，不允许修改，如用双引号包含起来的字符串
//(5)相当于C语言中的程序代码区。