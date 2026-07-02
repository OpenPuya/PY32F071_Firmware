================================================================================
                                样例使用说明
                                Sample Description
================================================================================
功能描述：
此样例演示了TIM1的输入捕获功能。配置PA8为通道1的输入引脚,每当引脚电平出现上升沿
时会触发捕获中断,并在中断处理中翻转LED。

Function descriptions:
This sample demonstrates the input capture functionality of TIM1 . Configure 
PA8 as the input capture pin. Whenever an rising edge is detected on PA8, it 
triggers the capture interrupt and toggles the LED in the interrupt callback 
function.
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
1. 编译下载程序到MCU,并运行
2. PA8每给一次上升沿,LED灯翻转一次

Example execution steps:
1.Compile and download the program to the MCU, and then run it.
2.Generate a rising edge on the PA8 pin, and the LED will toggle.
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