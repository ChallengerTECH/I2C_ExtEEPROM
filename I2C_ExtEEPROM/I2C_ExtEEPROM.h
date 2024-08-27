//REV = 0.2

#ifndef I2C_ExtEEPROM_H
#define I2C_ExtEEPROM_H

#include <Arduino.h>
#include <Wire.h>

class I2C_ExtEEPROM {
  public:
     //constructure
     I2C_ExtEEPROM(int EEPROMDensity, byte EEPROMAddress);

     //Methods
      void begin();
	  
	  void floatUpdate(unsigned int address, float value);
	  
	  float floatRead(unsigned int address);
      
      byte stringWrite (unsigned int eeaddress, byte *data, byte datalen = 1);

      byte byteWrite (unsigned int eeaddress, byte data ); 
      
      byte stringRead (unsigned int eeaddress, byte *data, byte datalen = 1);
      
      byte byteRead (unsigned int eeaddress);
      
      byte stringUpdate (unsigned int eeaddress, byte *data, byte datalen = 1);
      
      byte byteUpdate (unsigned int eeaddress, byte data);
	  
	  unsigned long int length ();
	  
	  String formatter(unsigned long int value, int digits, char pad);

      private:
          byte _EEPROMAddress;
          //unsigned long int _EEPROMDensity;
};


#endif
