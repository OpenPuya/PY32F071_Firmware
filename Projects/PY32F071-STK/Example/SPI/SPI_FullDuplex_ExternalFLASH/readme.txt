================================================================================
                                样例使用说明
                                Sample Description
================================================================================
功能描述：
此样例演示了主机SPI通过轮询方式进行通讯，从机使用FLASH外设芯片P25Q64，按下user
按键，主机先向从机写15bytes数据为0x1~0xf，然后再从FLASH中将写入的数据读出，读取成
功后，主机板上的小灯处于“常亮”状态。

Function descriptions:
This sample demonstrates the host SPI communication through polling, the slave 
uses FLASH peripheral chip P25Q64, press the user button, the host first to the 
slave to write 15bytes of data for the 0x1 ~ 0xf, and then from the FLASH will 
be written to read out the data, read the success of the host board, the small 
light is in the “always on” state! After successful reading, the small light on 
the host board is in the “always on” state.
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
2. 按下主机user按键，擦除外接FLASH第一个Sector页；
3. 写15bytes数据0x1-0xf到刚擦除的Sector页；
4. 从FLASH的第一个Sector页读取15bytes数据；
5. 比较读出的数据与写入的数据是否相同。主机的LED灯由常暗转为常亮状态，则表明主机
收发数据成功；当主机LED灯处于闪烁状态，则表明主机收发数据失败。

Example execution steps:
1. compile and download the program to MCU and run it;
2. Press the host user button to erase the first Sector of the external FLASH;
3. Write 15bytes of data 0x1-0xf to the Sector that was just erased;
4. read 15bytes of data from the first Sector of FLASH;
5. Compare whether the read data and the written data are the same. When the LED 
of the host turns from dark to light, it indicates that the host is successful in
sending and receiving data; when the LED of the host is in flashing state, it 
indicates that the host fails to send and receive data.
================================================================================
注意事项：
如果需要使用按键:
StartKit版本为V2.0以下,需将StartKit.h中的StartKitVersion 2 注释掉，并打开
StartKitVersion 1
StartKit版本为V2.0及以上版本,则无需操作
1.主机与从机引脚连接(箭头指向为信号传输方向) 
主机MASTER：         FLASH：
NSS(PA4)   ----->    NSS
SCK(PB3)   ----->    SCK
MISO(PB4)  <-----    MISO
MOSI(PB5)  ----->    MOSI
2.开发板焊接了FLASH器件，使用该样例需要焊接R44/R47/R48/R49/R50五个电阻。没有焊接
FLASH器件，使用该样例需外接FLASH。

Notes:
If you need to use buttons:
StartKit version is below V2.0, you need to comment StartKitVersion 2 in
StartKit.h, and open StartKitVersion 1 
StartKit version is V2.0 and above, no operation is required
1.The host is connected to the SLAVE pin (the arrow points in the signal 
transmission direction).
MASTER：             FLASH：
NSS(PA4)   ----->    NSS
SCK(PB3)   ----->    SCK
MISO(PB4)  <-----    MISO
MOSI(PB5)  ----->    MOSI
2.Development board welded FLASH device, the use of the sample need to weld
R44/R47/R48/R49/R50 five resistors. No FLASH device is soldered, using the sample
requires external FLASH.
================================================================================
