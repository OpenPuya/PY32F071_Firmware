================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了OPA的电压跟随功能，PA7为正端输入，PA6为负端输入，PA5为输出，PA5会输出
和PA7相同的电压值。

Function descriptions:
This sample demonstrates the voltage follower functionality of the OPA. PA7 
is the positive input, PA6 is the negative input, and PA5 is the output. PA5 
will output the same voltage as PA7.
================================================================================
测试环境：
测试用板：PY32F071_STK
MDK版本：5.28
IAR版本： 9.20
GCC 版本：GNU Arm Embedded Toolchain 10.3-2021.10

Test environment:
Test board: PY32F071_STK
MDK Version: 5.28
IAR Version: 9.20
GCC Version: GNU Arm Embedded Toolchain 10.3-2021.10
================================================================================
使用步骤：
1. 编译并下载程序。
2. 将PA5和PA6短接。
3. 在PA7端输入1V、2V、3V，观察PA5端检测到的电压值，应与PA7端输入的电压值相同。

Example execution steps:
1. Compile and download the program.
2. Short PA5 and PA6 together.
3. Input 1V, 2V, and 3V at the PA7 pin. Observe the voltage detected at the 
PA5 pin, which should be the same as the input voltage at PA7.
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
