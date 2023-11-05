/**********************************************************************
* File Name : XMC1100_RFID_Access_Cfg.h
* 
* Description : header file for the Configuration of the of the RFID_Access
*
* Author : Mohamed Bedair
*
* Date : 05 Nov 2023
*
**********************************************************************/


#ifndef XMC1100_RFID_ACCESS_CFG
#define XMC1100_RFID_ACCESS_CFG

#include <stdint.h>


#define ALLOWED_RFID_CARDS_COUNT      1
#define UID_LENGHT                    4


extern const uint8_t RFID_Card_List[ALLOWED_RFID_CARDS_COUNT][UID_LENGHT];





#endif