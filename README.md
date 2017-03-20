This is a project for UART communication between the VESC and a Beaglebone Black.

These UART APIs are based on the original stm32f4 UART project by vedderb:
https://github.com/vedderb/bldc_uart_comm_stm32f4_discovery 

He has written a tutorial on how to use and port this code to other platforms here:
http://vedder.se/2015/10/communicating-with-the-vesc-using-uart/

I have included a c++ wrapper that condenses the amount of code
required to perform control tasks over UART.

Examples have been provided for both API testing and Wrapper testing
in main.c and main.cpp. 

main.c demonstrates how to use the original
APIs from vedderb to do control over UART. main.cpp demonstrates how to
use the wrapper that I have implemented for UART control.

UART APIs can be compiled with either C or C++ compilers, but the
wrapper can only be compiled using c++. You can use the APIs in C
without the wrapper.

This project can be used with other linux platforms by changing MODEMDEVICE in comm_uart.c.

Enable Beaglebone Black UART1 in /boot/uEnv.txt. Make sure to use the correct line
for your version of the Linux Kernel.

