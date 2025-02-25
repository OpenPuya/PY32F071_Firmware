================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了ADC模块的Vrefint采样功能，通过采样Vrefint的值，计算得出VCC的值，并
通过串口打印出来。

Function descriptions:
This example demonstrates the Vrefint sampling function of the ADC module. By
sampling the value of Vrefint, the VCC value is calculated and printed through
the serial port.
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
2. 串口每隔1s打印VCC的电压值。

Example execution steps:
1. Compile and download the program and run it;
2. The serial port prints the voltage value of the VCC every 1 second.
================================================================================
注意事项：
通过USB转TTL模块连接PC与STK板,STK板与USB转TTL模块的连线方式如下；
STK板        USB转TTL模块
PA02(TX)  -->  RX
PA03(RX)  -->  TX
GND       -->  GND

Notes:
Connect the PC to the STK board through the USB to TTL module, the connection
between the STK board and the USB to TTL module is as follows:
STK board      USB to TTL module
PA02(TX)  -->  RX
PA03(RX)  -->  TX
GND        --> GND
================================================================================