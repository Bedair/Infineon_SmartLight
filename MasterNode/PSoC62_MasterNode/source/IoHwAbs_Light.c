/**********************************************************************
* File Name : IoHwAbs_Mic.c
* 
* Description : source file for the component responsible for controlling 
                the Microphone to capture sound
*
* Author : Mohamed Bedair
*
* Date : 05 Oct 2023
*
**********************************************************************/

/**********************************************************************
*                            Macro Section                            *
**********************************************************************/

#include "IoHwAbs_Mic.h"


#include "cybsp.h"
#include "cyhal.h"
#include "cycfg.h"


#define LIGHT_PIN           (CYBSP_USER_LED)
#define PWM_FREQUENCY       (1000000u)
#define FULL_DUTYCYCLE     (100)
#define ZERO_DUTYCYCLE     (0)

/**********************************************************************
*                          Global Variables                           *
**********************************************************************/
cyhal_pwm_t pwm_led;


/**********************************************************************
*                           Local Functions                           *
**********************************************************************/



/**********************************************************************
*                          Global Functions                           *
**********************************************************************/
/*
* Funcation Name : IoHwAbs_Light_Init
* Description    : Used to initialize light module
* Parameters     : NA
* Return         : NA
*/
void IoHwAbs_Light_Init(void)
{
    /* Initialize a PWM resource for driving an LED. */
    cyhal_pwm_init(&pwm_led, LIGHT_PIN, NULL);
    cyhal_pwm_set_duty_cycle(&pwm_led, ZERO_DUTYCYCLE,PWM_FREQUENCY);
    cyhal_pwm_start(&pwm_led);
}   


/*
* Funcation Name : IoHwAbs_Light_On
* Description    :Set the Light State to ON 
* Parameters     : NA
* Return         : NA
*/
void IoHwAbs_Light_On(void)
{
    cyhal_pwm_set_duty_cycle(&pwm_led, ZERO_DUTYCYCLE, PWM_FREQUENCY);
}


/*
* Funcation Name : IoHwAbs_Light_Off
* Description    : Set the Light State to OFF
* Parameters     : NA
* Return         : NA
*/
void IoHwAbs_Light_Off(void)
{
    cyhal_pwm_set_duty_cycle(&pwm_led, FULL_DUTYCYCLE, PWM_FREQUENCY);
}


/*
* Funcation Name : IoHwAbs_Light_Set_Brightness
* Description    : Used to set the brightness value
* Parameters     : NA
* Return         : NA
*/
void IoHwAbs_Light_Set_Brightness(uint8_t brightness)
{
    cyhal_pwm_set_duty_cycle(&pwm_led, brightness ,PWM_FREQUENCY);
}


