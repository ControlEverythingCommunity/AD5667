// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// AD5667
// This code is designed to work with the AD5667_I2CDAC I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Digital-Analog?sku=AD5667_I2CDAC#tabs-0-product_tabset-2

#include<Wire.h>

// AD5667 I2C address is 0x0E(14)
#define Addr 0x0E

void setup()
{
  // Initialise I2C communication as Master
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(9600);
  delay(300);
}

void loop()
{
  word data = 0x8000;
  
  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select DAC and input register
  Wire.write(0x1F);
  // Write data = 0x8000(32768)
  // data msb = 0x80
  Wire.write(highByte(data));
  // data lsb = 0x00
  Wire.write(lowByte(data));
  // Stop I2C transmission
  Wire.endTransmission();

  // Convert the data, Vref = 5 V
  float voltage = (( highByte(data) * 256 + lowByte(data)) / 65535.0) * 5.0;

  // Output data to serial monitor
  Serial.print("Voltage : ");
  Serial.print(voltage);
  Serial.println(" V");
  delay(500);
}
