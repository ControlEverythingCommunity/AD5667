// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// AD5667
// This code is designed to work with the AD5667_I2CDAC I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Digital-Analog?sku=AD5667_I2CDAC#tabs-0-product_tabset-2

import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;

public class AD5667
{
	public static void main(String args[]) throws Exception
	{
		// Create I2C bus
		I2CBus Bus = I2CFactory.getInstance(I2CBus.BUS_1);
		// Get I2C device, AD5667 I2C address is 0x0E(14)
		I2CDevice device = Bus.getDevice(0x0E);
		
		// Select DAC and input registers, write 2 bytes of data
		byte[] data = new byte[3];
		data[0] = 0x1F;
		data[1] = (byte)0x80;
		data[2] = (byte)0x00;
		device.write(data, 0, 3);
		
		Thread.sleep(500);
	}
}