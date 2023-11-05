/**********************************************************************
* File Name : XMC1100_RFID_Access.ino
* 
* Description : Arduino Code to read and Validate RFID Cards
*
* Author : Mohamed Bedair
*
* Date : 05 Nov 2023
*
**********************************************************************/


#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
PN532_I2C pn532i2c(Wire);
PN532 nfc(pn532i2c);	


#include "XMC1100_RFID_Access_Cfg.h"

#define NO_RFID_CARD      0xA5
#define VALID_RFID_CARD   0xAA
#define INVAILD_RFID_CARD 0x55


bool RFID_Card_Allowed(uint8_t* uid);

void setup(void) {
  Serial.begin(115200);
  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); 
  }

  nfc.setPassiveActivationRetries(0xF0);

  // configure board to read RFID tags
  nfc.SAMConfig();
}


void loop(void) {
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0 };  
  uint8_t uidLength;                        
    
  /* Wait for an ISO14443A type cards */
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);


  if (success) 
  {
    RFID_Card_Allowed(uid);
  }
  else
  {
    Serial.print(NO_RFID_CARD, HEX);
  }
  
}


bool RFID_Card_Allowed(uint8_t* uid)
{

  for (uint8_t card = 0; card < ALLOWED_RFID_CARDS_COUNT; card++)
  {
    if (
      (uid[0] == RFID_Card_List[card][0]) &&
      (uid[1] == RFID_Card_List[card][1]) &&
      (uid[2] == RFID_Card_List[card][2]) &&
      (uid[3] == RFID_Card_List[card][3])
    )
    {
      Serial.print(VALID_RFID_CARD, HEX);
    }
    else
    {
      Serial.print(INVAILD_RFID_CARD, HEX);
    }
    delay(200);
  }
}
