/**********************************************************************
* File Name : XMC1100_RFID_Access_Cfg.h
* 
* Description : source file for the Configuration of the of the RFID_Access
*
* Author : Mohamed Bedair
*
* Date : 05 Nov 2023
*
**********************************************************************/




#include "XMC1100_RFID_Access_Cfg.h"


const uint8_t RFID_Card_List[ALLOWED_RFID_CARDS_COUNT][UID_LENGHT] = {
    {0x15, 0xEA, 0xAF, 0xAC}
};