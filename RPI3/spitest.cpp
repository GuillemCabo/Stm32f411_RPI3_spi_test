
/******************************************************************************

A brief demonstration of the Raspberry Pi SPI interface
Resources:

This example makes use of the Wiring Pi library.
The wiringPi SPI API is documented here:
https://projects.drogon.net/raspberry-pi/wiringpi/spi-library/

The init call returns a standard file descriptor.  More detailed configuration
of the interface can be performed using ioctl calls on that descriptor.
See the wiringPi SPI implementation (wiringPi/wiringPiSPI.c) for some examples.
Parameters configurable with ioctl are documented here:
http://git.kernel.org/cgit/linux/kernel/git/torvalds/linux.git/tree/Documentation/spi/spidev

Hardware connections:

The board was connected as follows:
GND  -> GND
3.3V -> Vcc
CE1  -> SS (Shift Select)
SCK  -> SCK 
MOSI -> SDI
MISO -> SDO

To build this file, I use the command:
>  g++ spitest.cpp -lwiringPi

Then to run it, first the spi kernel module needs to be loaded.  This can be 
done using the GPIO utility.
> gpio load spi
> ./a.out

******************************************************************************/
#include <stdio.h>
#include <iostream>
#include <errno.h>
#include <wiringPiSPI.h>
#include <unistd.h>
#include <string>

using namespace std;

// channel is the wiringPi name for the chip select (or chip enable) pin.
// Set this to 0 or 1, depending on how it's connected.
static const int CHANNEL = 0;

int main()
{
   int fd, result;
   unsigned char buffer[]="HELLOstm";

   cout << "Initializing" << endl ;
   printf("%s\n",buffer);
   // Configure the interface.
   // CHANNEL insicates chip select,
   // 500000 indicates bus speed.
   fd = wiringPiSPISetup(CHANNEL,20000000);

   cout << "Init result: " << fd << endl;


   for(int i=0;i<2;i++)
   {
   	result = wiringPiSPIDataRW(CHANNEL, buffer, sizeof(buffer));
   	cout << "RW result: " << result << endl;
	printf("%s\n",buffer);
   }
}

