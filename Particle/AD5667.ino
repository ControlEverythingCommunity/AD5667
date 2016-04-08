// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// AD5667
// This code is designed to work with the AD5667_I2CDAC I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Digital-Analog?sku=AD5667_I2CDAC#tabs-0-product_tabset-2

#include <application.h>
#include <spark_wiring_i2c.h>

// AD5667 I2C address is 0x0E(14)
#define Addr 0x0E

float voltage = 0.0;
void setup()
{
  // Set variable
  Particle.variable("i2cdevice", "AD5667");
  Particle.variable("voltage", voltage);
  
  // Initialise I2C communication as Master
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(9600);
  delay(300);
}

void loop()
{
  unsigned int data[2] = {0x80, 0x00};
  
  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select DAC and input register
  Wire.write(0x1F);
  // Write data = 0x8000(32768)
  // data msb = 0x80
  Wire.write(data[0]);
  // data lsb = 0x00
  Wire.write(data[1]);
  // Stop I2C transmission
  Wire.endTransmission();

  // Convert the data, Vref = 5 V
  voltage = (((data[0] * 256) + (data[1])) / 65536.0) * 5.0;

  // Output data to dashboard
  Particle.publish("Voltage : ", String(voltage) + " V");
  delay(500);
  
}
