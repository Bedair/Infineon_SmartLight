/**********************************************************************
* File Name : App_Tasks.c
* 
* Description : source file for the component that contain implementation
*               for different OS tasks
*
* Author : Mohamed Bedair
*
* Date : 01 Oct 2023
*
**********************************************************************/

/**********************************************************************
*                            Macro Section                            *
**********************************************************************/

#include "App_Tasks.h"
#include "FreeRTOS.h"
#include "task.h"

#include "IoHwAbs_CapSense.h"
#include "cybsp.h"
#include "cyhal.h"
#include "cycfg.h"



#define HIGH_PRIO_TASK_PERIODICITY  (5u)
#define LOW_PRIO_TASK_PERIODICITY   (10u)


/**********************************************************************
*                           Local Functions                           *
**********************************************************************/

/**********************************************************************
*                          Global Variables                           *
**********************************************************************/



/**********************************************************************
*                          Global Functions                           *
**********************************************************************/


void High_Prio_Task(void* param)
{
    TickType_t xLastWakeTime_High_Prio;

    cyhal_pwm_t pwm_led;

    (void)param;
    
    uint8_t brightness;

    /* Initialize The CapSense */
    IoHwAbs_CapSense_Tuner_Init();
    IoHwAbs_CapSense_Init();


    /* Initialize a PWM resource for driving an LED. */
    cyhal_pwm_init(&pwm_led, CYBSP_USER_LED, NULL);
    cyhal_pwm_set_duty_cycle(&pwm_led, 0,1000000u);
    cyhal_pwm_start(&pwm_led);

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime_High_Prio = xTaskGetTickCount ();
    for (;;)
    {
        // Wait for the next cycle.
        (void)xTaskDelayUntil( &xLastWakeTime_High_Prio, HIGH_PRIO_TASK_PERIODICITY );

        /* Canpture new CapSense measurement */
        IoHwAbs_CasSense_Start_Scan();
        while (!IoHwAbs_CapSense_Scan_Done());
        IoHwAbs_CapSense_Process();
        IoHwAbs_CapSense_Tuner_Update();



        if (IoHwAbs_CapSense_Get_Button0_State())
        {
            cyhal_gpio_write(P0_5, 0);
        }
        else if (IoHwAbs_CapSense_Get_Button1_State())
        {
            cyhal_gpio_write(P0_5, 1);
        }
        else
        {

        }

        if (IoHwAbs_CapSense_Get_Slider_State(&brightness))
        {
            cyhal_pwm_set_duty_cycle(&pwm_led,brightness ,1000000u);
        }

        

    }
}


void Low_Prio_Task(void* param)
{
    TickType_t xLastWakeTime_Low_Prio;

    (void)param;
    

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime_Low_Prio = xTaskGetTickCount ();
    for (;;)
    {
        // Wait for the next cycle.
        (void)xTaskDelayUntil( &xLastWakeTime_Low_Prio, LOW_PRIO_TASK_PERIODICITY );

    }
}