/***
   Update and Read from the External EEPROM method

   Stores byte values into the External EEPROM.
   These values will stay in the External EEPROM Lib when the board is
   turned off and may be retrieved later by Read command.

   byteUpdate function: gonna check if a value has not changed in the External EEPROM,
   it is not overwritten which would reduce the life span of the EEPROM unnecessarily.
   
  created 4 July 2020
  by Ali M.
  ali.challenger89@yahoo.command
  
 ***/
 
 
#include<I2C_ExtEEPROM.h>//Call the External EEPROM Lib






I2C_ExtEEPROM ExtEEPROM(256, 0x57);// (EEPROM intensity, address) 
                                   // for intensity, you may enter the Kbits only
                                   // like AT24C1024  enter 1024 only
                                   //      AT24C256	  enter 256  only					 

byte inNum = 20;//byte data to be stored in the External EEPROM.  
byte readNum = 0;//used to store the byte data that red from the External EEPROM 


void setup() {
	ExtEEPROM.begin();//Init the External EEPROM 
	Serial.begin(9600);//Init the Serial

	ExtEEPROM.byteUpdate (16384, inNum);//Update the data to the External EEPROM @ the mentioned address

	readNum = ExtEEPROM.byteRead (16384);//Read the data from the External EEPROM @ the mentioned address 
	Serial.println(readNum);//Print the results                                         
}

void loop() {
  // put your main code here, to run repeatedly:

}
