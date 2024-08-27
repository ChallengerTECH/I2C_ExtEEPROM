/***
   Update and Read from the External EEPROM method

   Stores strings values into the External EEPROM.
   These values will stay in the External EEPROM Lib when the board is
   turned off and may be retrieved later by Read command.

   stringUpdate function: gonna check if the string has not changed in the External EEPROM,
   it is not overwritten which would reduce the life span of the EEPROM unnecessarily.
   
  created 4 July 2020
  by Ali M.
 ***/
 
 
 #include<I2C_ExtEEPROM.h>//Call the External EEPROM Lib
 
 
 
I2C_ExtEEPROM ExtEEPROM(256, 0x57);// (EEPROM intensity, address) 
                                   // for intensity, you may enter the Kbits only
                                   // like AT24C1024  enter 1024 only
                                   //      AT24C256	  enter 256  only	

byte inName[] = "ok hammed @WDKLCoE";//String data to be stored in the External EEPROM. 
byte readName[sizeof inName] = "";//used to store the string data that red from the External EEPROM 


void setup() {
	ExtEEPROM.begin();//Init the External EEPROM 
	Serial.begin(9600);//Init the Serial

	//Update the string data to the External EEPROM @ the mentioned address
	ExtEEPROM.stringUpdate (10, inName, sizeof inName);



	//Read the string data from the External EEPROM @ the mentioned address 
	ExtEEPROM.stringRead (10, readName, sizeof readName - 1);


	Serial.println((char *) readName);  //Print the results                                             
}

void loop() {
  // put your main code here, to run repeatedly:

}
