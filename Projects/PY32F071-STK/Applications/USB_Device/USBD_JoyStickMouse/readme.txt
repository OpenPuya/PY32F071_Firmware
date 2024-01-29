================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了USB鼠标功能。
USB鼠标主要是借助USB HID类实现，将其模拟成一个USB鼠标设备，设备程序每隔1秒钟向
主机发送一次鼠标相对位置。在PC端，可以看到鼠标每隔1秒移动一次位置。

Function descriptions:
This sample demonstrates the USB mouse functionality. It utilizes the USB HID 
class to simulate a USB mouse device. The device program sends mouse relative 
positions to the host every 1 second. On the PC side, you can observe the mouse 
moving every 1 second.

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
2. 通过USB连接线，一端连接STK板，另一端连接PC电脑；
3. 在PC端，鼠标每隔1秒钟移动一次位置。

Example execution steps:
1. Download and run the program.
2. Connect the STK board to a PC using a USB cable.
3. On the PC side, the mouse will move every 1 second.

================================================================================
注意事项：
1. 在用户测试程序过程中，如果对USB接口进行热插拔，当重新插上USB线到PC端后，有可能鼠标
不再移动。这是因为程序在发送新的鼠标位置之前会检查上一次是否发送成功（通过检查
HID_STATE_BUSY标志位）。如果热插拔过程中导致USB通信失败一次，则会停止更新鼠标位置。为
了解决这个问题，您可以取消程序中对HID_STATE_BUSY标志位的判断，这样就可以实现热插拔不影
响鼠标移动。

Notes:
1. During user testing, if the USB interface is hot-plugged, the mouse movement 
may stop after reconnecting the USB cable to the PC. This is because the program 
checks if the previous mouse position update was successful (by checking the 
HID_STATE_BUSY flag) before sending a new position. If there is a USB 
communication failure during the hot-plug process, the mouse position update 
will be halted. To address this issue, you can remove the check for the 
HID_STATE_BUSY flag in the program, allowing the mouse movement to continue 
even after hot-plugging.
================================================================================
