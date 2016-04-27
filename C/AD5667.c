// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// AD5667
// This code is designed to work with the AD5667_I2CDAC I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Digital-Analog?sku=AD5667_I2CDAC#tabs-0-product_tabset-2

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

void main() 
{
	// Create I2C bus
	int file;
	char *bus = "/dev/i2c-1";
	if((file = open(bus, O_RDWR)) < 0) 
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, AD5667 I2C address is 0x0E(14)
	ioctl(file, I2C_SLAVE, 0x0E);

	// Select DAC and input registers, write 2 bytes of data(0x1F)
	char config[3] = {0};
	config[0] = 0x1F;
	config[1] = 0x80;
	config[2] = 0x00;
	write(file, config, 3);
	sleep(1);

	// Convert the data
	float voltage = ((config[1] * 256 + config[2]) / 65536.0) * 5.0;

	// Output data to screen
	printf("Voltage : %.2f V \n", voltage);
}
