/**********************************************************************
* File Name : IoHwAbs_Communication.c
* 
* Description : source file for the component responsible for Communicating 
*               with the RFID Access node.
*
* Author : Mohamed Bedair
*
* Date : 05 Nov 2023
*
**********************************************************************/


#ifndef IOHWABS_COMMUNICATION_H_
#define IOHWABS_COMMUNICATION_H_

#include <stdint.h>

/*
* Funcation Name : IoHwAbs_Communication_Init
* Description    : Used to initialize Communication module
* Parameters     : NA
* Return         : NA
*/
void IoHwAbs_Communication_Init(void);


/*
* Funcation Name : IoHwAbs_Communication_Valid_Access
* Description    : Used to initialize Communication module
* Parameters     : NA
* Return         : True if the RFID Access detect a valid Card
*/
uint8_t IoHwAbs_Communication_Valid_Access(void);






#endif