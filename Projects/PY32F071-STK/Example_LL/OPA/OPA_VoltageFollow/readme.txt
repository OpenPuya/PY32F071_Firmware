================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了OPA的电压跟随功能。PA7为正端输入，PA6为负端输入，PA5为输出，PA5会
输出和PA7相同的电压值。

Function descriptions:
This sample demonstrates the voltage follower functionality of the OPA 
(Operational Amplifier). PA7 is the positive input, PA6 is the negative input, 
and PA5 is the output. PA5 will output the same voltage as PA7.
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
1. 编译并下载程序；
2. 将PA5和PA6短接；
3. 将1V、2V、3V分别输入到PA7端，检测PA5端输出的电压应分别为1V、2V、3V。

Example execution steps:
1. Compile and download the program to the MCU.
2. Short-circuit PA5 and PA6.
3. Input voltages of 1V, 2V, and 3V to the PA7 pin. The voltage measured at the 
   PA5 pin should be 1V, 2V, and 3V respectively.
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
