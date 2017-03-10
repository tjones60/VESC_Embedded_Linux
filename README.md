This is a project for UART communication between the VESC and a Beaglebone Black.
  
Enable UART in /boot/uEnv.txt.

Project can be compiled with either C or C++ compilers.

APIs can be used with other linux platforms by changing MODEMDEVICE in comm_uart.c.

A console interface is implemented in main.c for testing.
  
These APIs are based on the original stm32f4 UART project by vedderb:
https://github.com/vedderb/bldc_uart_comm_stm32f4_discovery 

He has written a tutorial on how to use and port this code to other platforms here:
http://vedder.se/2015/10/communicating-with-the-vesc-using-uart/

