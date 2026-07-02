================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了FreeRTOS队列集的相关API函数应用，实现队列的入队和出队，信号量释放和
获取。通过打印log，观察出队/入队和释放/获取实现过程。

Function descriptions:
This sample demonstrates the application of FreeRTOS queue set related API 
functions to implement queue in and queue out, semaphore release and fetch. 
Observe the queue-out/queue-in and release/acquire implementations by printing 
a log.

================================================================================
测试环境：
测试用板：PY32F071_STK
MDK版本：5.28
IAR版本：9.20
GCC版本：GNU Arm Embedded Toolchain 10.3-2021.10

Test environment:
Test board: PY32F071_STK
MDK Version: 5.28
IAR Version: 9.20
GCC Version: GNU Arm Embedded Toolchain 10.3-2021.10

================================================================================
使用步骤：
1. 编译下载程序到MCU，并运行；
2. 通过串口调试助手打印的log信息，观察任务执行过程。
   Task1: 任务执行1s后向队列发送一个值。任务执行2s后释放一个信号量，计时清零，并
          重复这两个步骤。
   Task2: 从队列集中获取任务句柄，任务句柄为队列句柄，打印队列中存放的数值。任务
          句柄是信号量句柄，打印“Take semaphore succuss!”信息。

Example execution steps:
1. Compile and download the program to the MCU and run it;
2. You can use the log information printed by the serial debugging assistant to 
observe the task execution process.
   Task1: Sends a value to the queue after the task is executed for 1s. Release
          a semaphore after the task is executed for 2s, time clear, and repeat
          these two steps.
   Task2: Obtains the task handle from the queue set. The task handle is the queue
          handle and prints the value stored in the queue. The task handle is a 
          semaphore handle that prints "Take semaphore succuss!" Message.

================================================================================
注意事项：
如果需要使用按键:
StartKit版本为V2.0以下,需将StartKit.h中的StartKitVersion 2 注释掉，并打开
StartKitVersion 1
StartKit版本为V2.0及以上版本,则无需操作
通过USB转TTL模块连接PC与STK板,STK板与USB转TTL模块的连线方式如下；
@PrintfConfigStart
STK板        USB转TTL模块
PA02(TX)  -->  RX
PA03(RX)  -->  TX
GND       -->  GND
UART配置为波特率115200，数据位8，停止位1，校验位None
@PrintfConfigEnd

Notes:
If you need to use buttons:
StartKit version is below V2.0, you need to comment StartKitVersion 2 in
StartKit.h, and open StartKitVersion 1 
StartKit version is V2.0 and above, no operation is required
Connect the PC to the STK board through the USB to TTL module, and the connection
method between the STK board and the USB to TTL module is as follows:
@PrintfConfigStart
STK board USB to TTL module
PA02(TX)  -->  RX
PA03(RX)  -->  TX
GND       -->  GND
UART is configured as BaudRate 115200, data bit 8, stop bit 1, and parity None.
@PrintfConfigEnd
================================================================================
