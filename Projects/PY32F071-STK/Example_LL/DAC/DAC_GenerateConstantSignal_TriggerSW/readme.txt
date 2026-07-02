================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了DAC的输出功能，通过PA4输出1/2供电电压的值。

Function descriptions:
This example demonstrates the output function of DAC, which outputs a value of
1/2 supply voltage through PA4.
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
2. 万用表测量PA4的电压，为供电电压的一半值，即供电电压为3.3V时，则输出1.65V.

Example execution steps:
1. compile and download the program to MCU and run it;
2. The multimeter measures the voltage of PA4, which is half of the supply
voltage. When the supply voltage is 3.3V, the output is 1.65V
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