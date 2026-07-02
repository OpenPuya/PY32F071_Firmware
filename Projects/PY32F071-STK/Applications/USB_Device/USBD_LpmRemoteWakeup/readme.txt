================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了USB挂起进入低功耗和远程唤醒功能。
USB键盘主要是借助USB HID类实现，将其模拟成一个USB键盘设备。设备程序运行后会LED点亮，
在PC挂起后，设备进入低功耗模式，当PC再次通讯时，LED熄灭，设备退出低功耗。同时，如果
在PC挂起后，按下按键，设备发出远程唤醒信号，唤醒PC。

Function descriptions:
This sample demonstrates the USB keyboard functionality. It utilizes the 
USB HID class to simulate a USB keyboard device. After the device program is run,
the LED will light up. When the PC enters suspend mode, the device enters 
low-power mode. When the PC communicates again, the LED turns off, and the device
exits low-power mode. Additionally, if a button is pressed while the PC is in 
suspend mode, the device sends a remote wakeup signal to wake up the PC

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
2. 设备通过USB连接电脑，让PC休眠，LED亮起，当PC退出休眠时，LED熄灭；
3. 设备通过USB连接电脑，让PC休眠，LED亮起，按下按键，PC退出休眠。

Example execution steps:
1. Download and run the program.
2. The device is connected to the PC via USB. When the PC enters sleep mode, the 
LED lights up. When the PC exits sleep mode, the LED turns off.
3. The device is connected to the PC via USB. When the PC enters sleep mode, the 
LED lights up. Pressing a button causes the PC to exit sleep mode.

================================================================================
注意事项：
如果需要使用按键:
StartKit版本为V2.0以下,需将StartKit.h中的StartKitVersion 2 注释掉，并打开
StartKitVersion 1
StartKit版本为V2.0及以上版本,则无需操作

Notes:
If you need to use buttons:
StartKit version is below V2.0, you need to comment StartKitVersion 2 in
StartKit.h, and open StartKitVersion 1 
StartKit version is V2.0 and above, no operation is required

================================================================================
