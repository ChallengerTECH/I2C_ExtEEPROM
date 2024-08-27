/***
   Update and Read from the External EEPROM method

   Stores float values into the External EEPROM.
   These values will stay in the External EEPROM Lib when the board is
   turned off and may be retrieved later by Read command.

   floatUpdate function: gonna check if a float value has not changed in the External EEPROM,
   it is not overwritten which would reduce the life span of the EEPROM unnecessarily.
   
  created 4 July 2020
  by Ali M.
  ali.challenger89@yahoo.com
  https://github.com/ChallengerTECH/I2C_ExtEEPROM
 ***/
 
 
 
 #include<I2C_ExtEEPROM.h>//Call the External EEPROM Lib
 
 
 
 

I2C_ExtEEPROM ExtEEPROM(256, 0x57);// (EEPROM intensity, address) 
                                   // for intensity, you may enter the Kbits only
                                   // like AT24C1024  enter 1024 only
                                   //      AT24C256	  enter 256  only					 

float valueToStore = 99.1; //float data to be stored in the External EEPROM.  
int memoryAddress = 0; // Starting memory address



void setup() {
	ExtEEPROM.begin();//Init the External EEPROM 
	Serial.begin(9600);//Init the Serial

	Serial.println("Storing " + String(valueToStore) + " in the EEPROM Cell " + String(memoryAddress));

    //Update the float to the External EEPROM @ the mentioned address	
	ExtEEPROM.floatUpdate(memoryAddress, valueToStore);
	
	//Read the float from the External EEPROM @ the mentioned address 
	float readNum = ExtEEPROM.floatRead(memoryAddress);

	//Print the results  
	Serial.println(String(readNum) + " Red from the EEPROM Cell " + String(memoryAddress));
                                             
}

void loop() {
  // put your main code here, to run repeatedly:

}
