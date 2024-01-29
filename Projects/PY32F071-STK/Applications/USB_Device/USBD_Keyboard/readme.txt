================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了USB键盘功能。
USB键盘主要是借助USB HID类实现，将其模拟成一个USB键盘设备。设备程序运行后会不断
向主机发送字母a。在PC端，打开一个文本文档，可以看到文本中会自动持续地输入字母a。

Function descriptions:
This sample demonstrates the USB keyboard functionality. It utilizes the 
USB HID class to simulate a USB keyboard device. The device program continuously 
sends the letter 'a' to the host. On the PC side, open a text document, switch 
to English input method, and ensure the text document input window is selected. 
You will see the letter 'a' being automatically and continuously inputted into 
the text document.

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
2. 在PC电脑上打开一个文本文档，输入法改成英文输入，并用鼠标选中文档输入窗口；
3. 通过USB连接线，一端连接STK板，另一端连接PC电脑；
4. 在文本文档中，会持续输入字母'a'；

Example execution steps:
1. Download and run the program.
2. Open a text document on your PC, switch to English input method, and ensure 
the text document input window is selected.
3. Connect the STK board to the PC using a USB cable.
4. The letter 'a' will be continuously inputted into the text document.

================================================================================
注意事项：
1. 在用户测试程序过程中，如果对USB接口进行热插拔，当重新插上USB线到PC端后，有可
能上位机不会再收到数据。这是因为程序在发送新数据之前会检查上一次是否发送成功（通
过检查HID_STATE_BUSY标志位）。如果热插拔过程中导致USB通信失败一次，则会停止发送
数据。为了解决这个问题，您可以取消程序中对HID_STATE_BUSY标志位的判断，这样就可以
实现热插拔不影响数据发送。

Notes:
1. During user testing, if the USB interface is hot-plugged, it is possible 
that the host will no longer receive data after reconnecting the USB cable to 
the PC. This is because the program checks if the previous data transmission 
was successful (by checking the HID_STATE_BUSY flag) before sending new data. 
If there is a USB communication failure during the hot-plug process, data 
transmission will be halted. To address this issue, you can remove the check 
for the HID_STATE_BUSY flag in the program, allowing data transmission to 
continue even after hot-plugging.
================================================================================
