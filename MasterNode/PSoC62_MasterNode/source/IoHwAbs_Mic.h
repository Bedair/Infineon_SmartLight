/**********************************************************************
* File Name : IoHwAbs_Mic.h
* 
* Description : header file for the component responsible for controlling 
                the Microphone to capture sound
*
* Author : Mohamed Bedair
*
* Date : 05 Oct 2023
*
**********************************************************************/


#ifndef IOHWABS_MIC_H_
#define IOHWABS_MIC_H_

#include <stdint.h>

/*
* Funcation Name : IoHwAbs_Mic_Init
* Description    : Used to initialize the interface used connect the Mic
* Parameters     : NA
* Return         : NA
*/
void IoHwAbs_Mic_Init(void);


/*
* Funcation Name : IoHwAbs_Mic_Get_Current_Value
* Description    : Used to get the current voltage value of the mic
* Parameters     : NA
* Return         : current voltage value of the mic 
*/
int16_t IoHwAbs_Mic_Get_Current_Value(void);


/*
* Funcation Name : IoHwAbs_Mic_Person_Presence
* Description    : Used to check if there is a person in the room based on the Mic level
* Parameters     : NA
* Return         : True if the Mic detect a nosie in the room
*/
uint8_t IoHwAbs_Mic_Person_Presence(void);


#endif