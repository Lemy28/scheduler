# scheduler
OS Course Design

SWU 操作系统课程设计

一个简单的通用调度机演示程序。


要求：
1．进程调度算法包括：时间片轮转算法、先来先服务算法、短作业优先算法、静态优先权优先调度算法、高响应比调度算法 。 
2．每一个进程有一个 PCB，其内容可以根据具体情况设定。 
3．进程数、进入内存时间、要求服务时间、作业大小、优先级等均可以在界面上设定。 
4．可读取样例数据（要求存放在外部文件中）进行进程数、进入内存时间、时间片长度、作业大小、进程优先级的初始化。 
5．可以在运行中显示各进程的状态：就绪、执行（由于不要求设置互斥资源与进程间的同步关系， 故只有两种状态） 
6．有性能比较功能，可比较同一组数据在不同调度算法下的平均周转时间。 
