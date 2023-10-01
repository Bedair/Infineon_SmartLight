/**********************************************************************
* File Name : IoHwAbs_CapSense.c
* 
* Description : Header file for the component responsible for abstracting
*               the CapSense Driver
*
* Author : Mohamed Bedair
*
* Date : 01 Oct 2023
*
**********************************************************************/


#ifndef IOHWABS_CAPSENSE_H_
#define IOHWABS_CAPSENSE_H_

#include <stdint.h>

typedef enum
{
    e_CapSense_Scan_Not_Done = 0,
    e_CapSense_Scan_Done
}CapSense_Scan_State;


typedef enum
{
    e_CapSense_Button_Released = 0,
    e_CapSense_Button_Pressed
}CapSense_Button_State;



/*
* Funcation Name : IoHwAbs_CapSense_Init
* Description    : Used to initialize the CapSense module
* Parameters     : NA
* Return         : NA
*/
void IoHwAbs_CapSense_Init(void);


/*
* Funcation Name : IoHwAbs_CapSense_Tuner_Init
* Description    : Used to initialize the CapSense tuner
* Parameters     : NA
* Return         : NA
*/
void IoHwAbs_CapSense_Tuner_Init(void);

/*
* Funcation Name : IoHwAbs_CapSense_Tuner_Update
* Description    : Used to send new measured values to the Tuner
* Parameters     : NA
* Return         : NA
*/
void IoHwAbs_CapSense_Tuner_Update(void);


/*
* Funcation Name : IoHwAbs_CasSense_Start_Scan
* Description    : Used to start new CapSense measurement
* Parameters     : NA
* Return         : NA
*/
void IoHwAbs_CasSense_Start_Scan(void);


/*
* Funcation Name : IoHwAbs_CapSense_Process
* Description    : Used to process the last CapSense scan results
* Parameters     : NA
* Return         : NA
*/
void IoHwAbs_CapSense_Process(void);


/*
* Funcation Name : IoHwAbs_CapSense_Scan_Done
* Description    : Used to check if the current CapSense scan is done or not
* Parameters     : NA
* Return         : whether Scan is done or not
*/
CapSense_Scan_State IoHwAbs_CapSense_Scan_Done(void);


/*
* Funcation Name : IoHwAbs_CapSense_Get_Button0_State
* Description    : Used to return the status of Button 0
* Parameters     : NA
* Return         : Button 0 Status
*/
CapSense_Button_State IoHwAbs_CapSense_Get_Button0_State(void);


/*
* Funcation Name : IoHwAbs_CapSense_Get_Button1_State
* Description    : Used to return the status of Button 1
* Parameters     : NA
* Return         : Button 1 Status
*/
CapSense_Button_State IoHwAbs_CapSense_Get_Button1_State(void);


/*
* Funcation Name : IoHwAbs_CapSense_Get_Slider_State
* Description    : Used to retuen the Silder value
* Parameters     : NA
* Return         : Current Slider value
*/
uint8_t IoHwAbs_CapSense_Get_Slider_State(void);

#endif