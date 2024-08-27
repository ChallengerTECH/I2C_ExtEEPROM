//# REV = 0.2


#include "I2C_ExtEEPROM.h"


unsigned long int _EEPROMDensity; // Declare a global variable to store ROM density 

I2C_ExtEEPROM::I2C_ExtEEPROM(int EEPROMDensity, byte EEPROMAddress){
  //for instantiating the object
  // Assign variables.
   _EEPROMDensity = EEPROMDensity;
   
  _EEPROMAddress = EEPROMAddress;
}

//Reference
//https://gammon.com.au/i2c

//////////////////begin method///////////////////
 void I2C_ExtEEPROM::begin(){
  Wire.begin();
 }

//method to return the EEPROM length
unsigned long int I2C_ExtEEPROM::length (){
	return ((_EEPROMDensity*1024)/8)-1;
}

float I2C_ExtEEPROM::floatRead(unsigned int address) {  //Serial.println("inside read");
  byte buffer[4]; // Buffer to store the bytes read from EEPROM

  Wire.beginTransmission(_EEPROMAddress);
  Wire.write((int)(address >> 8)); // MSB
  Wire.write((int)(address & 0xFF)); // LSB
  Wire.endTransmission();

  Wire.requestFrom(_EEPROMAddress, 4); // Request 4 bytes from EEPROM
  for (int i = 0; i < 4 && Wire.available(); i++) {
    buffer[i] = Wire.read();
  }

  float* floatPointer = (float*)buffer; // Cast byte array back to float
  return *floatPointer;
}


//function to update float to the EEPROM
void I2C_ExtEEPROM::floatUpdate(unsigned int address, float value) {
//call the float read to see if its already their
if (floatRead(address) != value){  
   byte* bytePointer = (byte*)&value; // Cast float to byte array
   Wire.beginTransmission(_EEPROMAddress);
   Wire.write((int)(address >> 8)); // MSB
   Wire.write((int)(address & 0xFF)); // LSB
   for (int i = 0; i < 4; i++) {
     Wire.write(bytePointer[i]);
   }
   Wire.endTransmission();
  delay(5); // Wait for the write cycle to complete
}
}

// Function to format the integer value as a fixed-width string
String I2C_ExtEEPROM::formatter(unsigned long int value, int digits, char pad) {
String formattedValue = String(value);
while (formattedValue.length() < digits) {
formattedValue = pad + formattedValue;
}
return formattedValue;
  }





//////////////////////////defines the multiWriteEEPROM function for external////////////////////////////
byte I2C_ExtEEPROM::stringWrite(unsigned int eeaddress, byte *data, byte datalen = 1) {

  //check the called cell address
//   #if (eeaddress > _EEPROMDensity) 
//          #define MaxdensityErr
//#endif
//   #ifdef MaxdensityErr
//                      #error ==> Wrong Cell address, might wrap address.
//  #endif
if (datalen > BUFFER_LENGTH)  // 32 (in Wire.h)
       return 0xFF;  // too long
        byte err;
    Wire.beginTransmission(_EEPROMAddress);
    Wire.write((byte)(eeaddress >> 8)); //writes the MSB
    Wire.write((byte)(eeaddress & 0xFF)); //writes the LSB
    Wire.write(data, datalen);
    err = Wire.endTransmission();
    delay(5);
    if (err != 0)
        return err;  // cannot write to device

    // wait for write to finish by sending address again
    //  ... give up after 100 attempts (1/10 of a second)   
    for (byte counter = 0; counter < 100; counter++)
        {
        delayMicroseconds (300);  // give it a moment
        Wire.beginTransmission (_EEPROMAddress);
        Wire.write ((byte) (eeaddress >> 8));    // high order byte
        Wire.write ((byte) (eeaddress & 0xFF));  // low-order byte
        err = Wire.endTransmission ();
        if (err == 0)
          break;
        }
       
      return err; 
}

//////////////////////////defines the byteWriteEEPROM function for external////////////////////////////
// write one byte to device, returns non-zero on error
  byte I2C_ExtEEPROM::byteWrite (unsigned int eeaddress, byte data ) 
    {
    return stringWrite (eeaddress, &data);
    } // end of writeEEPROM

//////////////////////////defines the multiReadEEPROM function for external////////////////////////////
byte I2C_ExtEEPROM::stringRead(unsigned int eeaddress, byte *data, byte datalen = 1) {
    if (datalen > BUFFER_LENGTH)  // 32 (in Wire.h)
        return 0xFF;  // too long
        
    byte rdata;
     
    Wire.beginTransmission(_EEPROMAddress);
    Wire.write((byte)(eeaddress >> 8));//writes the MSB
    Wire.write((byte)(eeaddress & 0xFF));//writes the LSB
    byte err = Wire.endTransmission();

    if (err != 0)
            return err;  // cannot read from device
    // initiate blocking read into internal buffer        
    Wire.requestFrom(_EEPROMAddress,datalen);
    // pull data out of Wire buffer into our buffer
    for (byte counter = 0; counter < datalen; counter++)
            {
            data [counter] = Wire.read ();
            }
return 0;  // OK
}

//////////////////////////defines the byteReadEEPROM function for external////////////////////////////
byte I2C_ExtEEPROM::byteRead(unsigned int eeaddress) {
    // read one byte from device, returns 0xFF on error
   byte temp; 
    if (stringRead (eeaddress, &temp) == 0)
      return temp;
  
    return 0xFF;
}
////////////////////defines the multiUpdateEEPROM function for external////////////////////////////
byte I2C_ExtEEPROM::stringUpdate(unsigned int eeaddress, byte *data, byte datalen = 1) {
 if (datalen > BUFFER_LENGTH)  // 32 (in Wire.h)
       return 0xFF;  // too long
    byte buff [datalen];   
    stringRead(eeaddress, buff, sizeof buff);
       bool ass = false;
      
     for (byte n=0;n<datalen;n++) 
         if (buff[n] != data[n]) {ass = true; break;  }
              
    if(ass ){//delay(50);
    Wire.beginTransmission(_EEPROMAddress);
    Wire.write((byte)(eeaddress >> 8)); //writes the MSB
    Wire.write((byte)(eeaddress & 0xFF)); //writes the LSB
    Wire.write(data, datalen);
    byte err = Wire.endTransmission();
    delay(5);
    if (err != 0)
        return err;  // cannot write to device

    // wait for write to finish by sending address again
    //  ... give up after 100 attempts (1/10 of a second)   
    for (byte counter = 0; counter < 100; counter++)
        {
        delayMicroseconds (300);  // give it a moment
        Wire.beginTransmission (_EEPROMAddress);
        Wire.write ((byte) (eeaddress >> 8));    // high order byte
        Wire.write ((byte) (eeaddress & 0xFF));  // low-order byte
        err = Wire.endTransmission ();
        if (err == 0)
          break;
        }
       
      return err; 
    }
}

////////////////////defines the byteUpdateEEPROM function for external////////////////////////////
byte I2C_ExtEEPROM::byteUpdate(unsigned int eeaddress, byte data) {

   //read byte to check whether the old data is same
   if (byteRead (eeaddress) != data)
return stringUpdate (eeaddress, &data);
   
else 
return 0xAA;  // same data no need to re-write
     

    }
