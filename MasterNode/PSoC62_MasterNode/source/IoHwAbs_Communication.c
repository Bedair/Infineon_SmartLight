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

/**********************************************************************
*                            Macro Section                            *
**********************************************************************/

#include "IoHwAbs_Communication.h"
#include "cycfg_peripherals.h"


#define VALID_RFID_CARD   0xAA
/**********************************************************************
*                          Global Variables                           *
**********************************************************************/
/* Allocate context for UART operation */
cy_stc_scb_uart_context_t uartContext;



/**********************************************************************
*                           Local Functions                           *
**********************************************************************/



/**********************************************************************
*                          Global Functions                           *
**********************************************************************/


/*
* Funcation Name : IoHwAbs_Communication_Init
* Description    : Used to initialize Communication module
* Parameters     : NA
* Return         : NA
*/
void IoHwAbs_Communication_Init(void)
{
    (void) Cy_SCB_UART_Init(SCB0, &scb_0_config, &uartContext);

    /* Enable UART to operate */
    Cy_SCB_UART_Enable(SCB0);
}


/*
* Funcation Name : IoHwAbs_Communication_Valid_Access
* Description    : Used to initialize Communication module
* Parameters     : NA
* Return         : True if the RFID Access detect a valid Card
*/
uint8_t IoHwAbs_Communication_Valid_Access(void)
{
    uint8_t retunValue = false;
    volatile uint32 UART_Received_Data;

    UART_Received_Data = Cy_SCB_UART_Get(SCB0);

    if (UART_Received_Data == VALID_RFID_CARD)
    {
        retunValue = true;
    }

    return retunValue;

}