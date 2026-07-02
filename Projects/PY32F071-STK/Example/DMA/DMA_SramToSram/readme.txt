================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了DMA从SRAM到SRAM传输数据的功能（SRAM和外设之间传输的样例请参考相关外设
样例工程）。

Function descriptions:
This example demonstrates the function of DMA transferring data from SRAM to
SRAM (please refer to the relevant peripheral sample project for the example
of transfer between SRAM and peripherals).
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
2. LED灯常亮，表明DMA传输完成并且数据正确；
3. LED灯闪烁，表明DMA传输出错或者DMA的数据传输的不正确。

Example execution steps:
1.Compile and download the program to MCU and run it;
2.The LED light is constantly on, indicating that DMA transmission is complete
and the data is correct;
3.The LED light flashes, indicating an error in DMA transmission or incorrect
data transmission from DMA.
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