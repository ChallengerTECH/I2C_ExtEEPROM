/***
   Sets all of the bytes of the External EEPROM to 0

   Can use either byteUpdate or byteWrite function to clear the External EEPROM cells.
   
   formatter Function: can be used to fix the data length by padding spaces or other chars.
   
   length function: Returns the max length of the External EEPROM cells.
   
  created 4 July 2020
  by Ali M.
 ***/
 
 
#include<I2C_ExtEEPROM.h>//Call the External EEPROM Lib



I2C_ExtEEPROM ExtEEPROM(256, 0x57);// (EEPROM intensity, address) 
                                   // for intensity, you may enter the Kbits only
                                   // like AT24C1024  enter 1024 only
                                   //      AT24C256	  enter 256  only		
										 
										 

byte readNum = 0;//used to buffer the EEPROM cell value 


void setup() {
  ExtEEPROM.begin();//Init the External EEPROM
  Serial.begin(9600);//Init the Serial for display
  
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  
  // initialize the LED pin as an output.
  pinMode(13, OUTPUT);
  
  
  //read the current values from the External EEPROM cells
  Serial.print(F("Reading the Original Values in the ROM Cells. \n"));
  CellsReadnPrint();//call a function to read and print on the serial monitor
												
  
  /***
    Iterate through each byte of the External EEPROM storage.

    Different External EEPROM have Different sizes, E.g:
    - AT24C1024:        131,072B EEPROM storage.
    - AT24C256:         32,768B EEPROM storage.
   

    Rather than hard-coding the length, you should use the pre-provided length function.
    This will make your code portable to all External EEPROM types.
  ***/

  Serial.print(F("Clearing the ROM Cells.\n"));
  for (unsigned long int i = 0 ; i <= ExtEEPROM.length() ; i++) {
	ExtEEPROM.byteUpdate (i, 0);//update   or:
	//ExtEEPROM.byteWrite (i, 0);//write
  }

  // turn the LED on when we're done
  digitalWrite(13, HIGH);
  
  //read the EEPROM cells after clearing.
  Serial.print(F("Reading the ROM Cells Value After Clearing. \n"));
  CellsReadnPrint();//call a function to read and print on the serial monitor
  
  Serial.print(F("DONE!. \n"));
}

void loop() {
  /** Empty loop. **/
}


void CellsReadnPrint(){//function to read and print on the serial monitor
                       //this function gonna print each 8 bytes in a row
	for(unsigned long int addr = 0; addr <= ExtEEPROM.length(); addr +=8)//Iterate for each row
        {		
		Serial.print(ExtEEPROM.formatter(addr, 6, ' '));//print the formatted Cells addresses
		Serial.print(F("     |  "));
		for(unsigned long int offset = addr; offset < (addr+8); offset++)//Iterate for each byte in the row
		  {
			 readNum = ExtEEPROM.byteRead (offset);//read from the External EEPROM
             Serial.print(ExtEEPROM.formatter(readNum, 3, ' '));//print the formatted data
			 Serial.print(F("  |  "));
			}
		   Serial.println();
		}
}