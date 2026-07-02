================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了flash sector擦除和page写功能。

Function descriptions:
This sample demonstrates the flash sector erase and page write functions.
================================================================================
测试环境：
测试用板：PY32F071_STK
MDK版本： 5.28
IAR版本： 9.20
GCC 版本：GNU Arm Embedded Toolchain 10.3-2021.10

Test environment:
Test board: PY32F071_STK
MDK Version: 5.28
IAR Version: 9.20
GCC Version: GNU Arm Embedded Toolchain 10.3-2021.10
================================================================================
使用步骤：
1. 编译下载程序到MCU，并运行；
2. 按下按键，程序进行sector擦除和page写功能；
3. sector擦除成功和page写成功，LED亮。

Example execution steps:
1. compile and download the program to the MCU and run it;
2. press the key, the program performs the function of sector erase and page 
write;
3. sector erase successfully and page write successfully, the LED lights up.
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