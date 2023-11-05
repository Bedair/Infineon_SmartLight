/**********************************************************************
* File Name : IoHwAbs_Light.h
* 
* Description : header file for the component responsible for controlling 
                the light
*
* Author : Mohamed Bedair
*
* Date : 05 Oct 2023
*
**********************************************************************/


#ifndef IOHWABS_LIGHT_H_
#define IOHWABS_LIGHT_H_

#include <stdint.h>


typedef enum {
    LIGHT_ON,
    LIGHT_OFF
}Light_State_T;

/*
* Funcation Name : IoHwAbs_Light_Init
* Description    : Used to initialize light module
* Parameters     : NA
* Return         : NA
*/
void IoHwAbs_Light_Init(void);


/*
* Funcation Name : IoHwAbs_Light_On
* Description    :Set the Light State to ON 
* Parameters     : NA
* Return         : NA
*/
void IoHwAbs_Light_On(void);


/*
* Funcation Name : IoHwAbs_Light_Off
* Description    : Set the Light State to OFF
* Parameters     : NA
* Return         : NA
*/
void IoHwAbs_Light_Off(void);


/*
* Funcation Name : IoHwAbs_Light_Set_Brightness
* Description    : Used to set the brightness value
* Parameters     : NA
* Return         : NA
*/
void IoHwAbs_Light_Set_Brightness(uint8_t brightness);



#endif