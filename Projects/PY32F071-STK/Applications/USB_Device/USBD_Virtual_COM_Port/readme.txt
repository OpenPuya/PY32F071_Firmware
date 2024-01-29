================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了USB虚拟串口功能（无UART功能）。
USB虚拟串口主要是借助USB CDC ACM类实现，将其模拟成一个VCP设备。当插在电脑上时，
可以将其显示为一个串口设备。与市面上的USB转TTL模块的区别在于，此样例只使用USB，
没有与串口（UART外设）进行连动。

Function descriptions:
This sample demonstrates the USB virtual serial port (VCP) functionality 
without UART support. It utilizes the USB CDC ACM class to simulate a VCP 
device. When connected to a computer, it appears as a virtual serial port 
device. The difference from USB-to-TTL modules on the market is that this 
sample only uses USB and does not interact with a serial port (UART peripheral).

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
3. 打开PC电脑上的设备管理器，可以发现多了一个COM口；
4. 打开串口调试助手，开启对应COM口，并使能DTR，串口调试助手每隔1s会收到128个字节数据
5. PC端串口发送一串数据（不超过128个字节）到设备，MCU通过debug模式查看read_buffer
数组，发现数据和PC端发送的数据一致

Example execution steps:
1. Download and run the program.
2. Connect the STK board to the PC using a USB cable.
3. Open the device manager on the PC and observe the appearance of a new 
COM port.
4. Open a serial terminal program, select the corresponding COM port, and 
enable DTR. The serial terminal program will receive 128 bytes of data 
every second.
5. On the PC side, send a string of data (up to 128 bytes) to the device 
using the serial terminal program. Check the read_buffer array in the MCU's 
debug mode to verify that the received data matches the data sent from the PC.

================================================================================
注意事项：
1. 在用户测试程序过程中，如果对USB接口进行热插拔，当重新插上USB线到PC端后，有可能
串口助手收不到数据。这是因为程序在发送数据之前会检查上一次是否发送成功（通过检查
ep_tx_busy_flag标志位）。如果热插拔过程中导致USB通信失败一次，则设备将停止向主机
发送数据。为了解决这个问题，您可以取消程序中对ep_tx_busy_flag标志位的检查，从而
实现热插拔不影响串口助手的数据接收。

Notes:
1. During user testing, if the USB interface is hot-plugged, it is possible 
that the serial terminal program will not receive data after reconnecting 
the USB cable to the PC. This is because the program checks if the previous 
data transmission was successful (by checking the ep_tx_busy_flag) before 
sending new data. If there is a USB communication failure during the hot-plug 
process, the device will stop sending data to the host. To address this issue, 
you can remove the check for the ep_tx_busy_flag in the program, allowing the 
serial terminal program to receive data even after hot-plugging.
================================================================================
