#include <Wire.h>


void setup() {
Wire.begin();//initilizing i2c
}

//variable declarations
int reading = 0 ;
double humidity = 0 , temperature = 0 ; 

void loop() {
  
Wire.beginTransmission(0x27);//default address for i2c bus in HIH8000 series
Wire.write(byte(0x00));//Initiate measurement by sending a zero bit 
Wire.endTransmission();//stop transmitting

/* Wait for 100ms for measurement to complete.
Typical measurement cycle is 36.65ms for each of humidity and 
temperature, so you may reduce this to 74ms. */
delay(100);
/* read back data */
Wire.requestFrom(0x27, 4);// request 4 bytes from slave device #0x27
if (4 <= Wire.available()) // if four bytes were received
{ 
/* Humidity is located in first two bytes */
reading = Wire.read();  // receive high byte (overwrites previous reading)
reading = reading << 8;// shift high byte to be high 8 bits
reading |= Wire.read(); // receive low byte as lower 8 bits
humidity = reading / 16382.0 * 100.0; //humidity conversion as per the documentation
reading = 0;//initilizing the reading to read the temperature values
/* Temperature is located in next two bytes, padded by two trailing bits */
reading = Wire.read();
reading = reading << 6;
reading |= (Wire.read()>>2);
temperature = reading / 16382.0 * 165.0 - 40;//temperature conversion as per documentations...
}
  }
    
