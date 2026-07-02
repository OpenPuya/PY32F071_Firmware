================================================================================
                                样例使用说明
================================================================================
功能描述：
此样例演示了USB U盘功能
USB U盘主要是借助 USB MSC 类实现，将PY25Q128模拟成16M的U盘
同时添加了FatFs文件系统，实现MCU读取外部Flash中的txt文件

Function descriptions:
This sample demonstrates the USB Udisk functionality.
USB Udisk is mainly implemented by USB MSC class, which simulates the PY25Q128
as a 16MB USB flash drive.
The FatFs file system has been added. The MCU can read txt files in the
external Flash.
================================================================================
测试环境：
测试用板：STK
MDK版本：5.28
IAR版本： 9.20
GCC 版本：GNU Arm Embedded Toolchain 10.3-2021.10

Test environment:
Test board: STK
MDK Version: 5.28
IAR Version: 9.20
GCC Version: GNU Arm Embedded Toolchain 10.3-2021.10
================================================================================
使用步骤：
1. 下载并运行程序；
2. 通过usb连接线，一端连接STK板，另一端连接PC电脑；
3. PC端显示出一个16Mbytes的U盘，可以在U盘中存储数据
4. 使用USB转串口工具连接电脑和STK板，在电脑端打开串口打印软件观察打印信息，依次
会打印出文件系统读测试过程中的信息，包括txt文件名、读出字符数、读出文本语句；
5. 首次使用时，若外部Flash中不存在"Test.txt"文件，文件系统读测试过程将无法正常
进行，会打印错误信息"Failed to open the file.",需要在电脑上打开U盘,并在其中创建
"Test.txt"文件，内容可自行编写，随后复位MCU重新运行程序，便可正常进行文件系统读
测试过程

Example execution steps:
1. Download and run the program;
2. Connect the STK board to the PC computer using the USB cable;
3. A 16Mbytes USB Udisk is displayed on the PC. Data can be stored on the 
USB Udisk.
4. Use a USB-to-serial tool to connect the computer and the STK board. Open the
serial port printing software on the computer to observe the printed
information. Sequentially, information during the file system read test process
will be printed, including the txt file name, number of characters read, and
read text sentences.
5. When using it for the first time, if the "Test.txt" file does not exist in
the external Flash, the file system read test process will not proceed normally,
and an error message "Failed to open the file." will be printed. You need to
open the USB flash drive on the computer and create a "Test.txt" file inside.
The content can be written by yourself. Then reset the MCU and rerun the
program, and the file system read test process can proceed normally.
================================================================================
注意事项：
如果需要使用按键:
StartKit版本为V2.0以下,需将StartKit.h中的StartKitVersion 2 注释掉，并打开
StartKitVersion 1
StartKit版本为V2.0及以上版本,则无需操作
1. 第一次使用时PC端会弹出格式化U盘，请按提示格式化U盘即可。
2. 此样例使用的是16M的flash
3. 和PY25Q128连接如下
PB6   -->  CS
PB3   -->  SCLK
PB4   -->  SO
PB5   -->  SI
PB10   -->  WP
PB11   -->  RESET
GND    -->  GND
通过USB转TTL模块连接PC与STK板,STK板与USB转TTL模块的连线方式如下；
@PrintfConfigStart
STK板        USB转TTL模块
PA02(TX)  -->  RX
PA03(RX)  -->  TX
GND       -->  GND
UART配置为波特率115200，数据位8，停止位1，校验位None
@PrintfConfigEnd

1. When you use the USB flash drive for the first time, format the USB Udisk as
prompted. 
2. This example uses the MCU of 16M flash. 
3. Connect to PY25Q128 as follows:
PB6   -->  CS
PB3   -->  SCLK
PB4   -->  SO
PB5   -->  SI
PB10   -->  WP
PB11   -->  RESET
GND    -->  GND
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