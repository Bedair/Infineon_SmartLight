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
#include "IoHwAbs_Light.h"
#include "IoHwAbs_Mic.h"


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

    

    (void)param;
    
    uint8_t brightness;


    IoHwAbs_Light_Init();

    /* Initialize The CapSense */
    IoHwAbs_CapSense_Tuner_Init();
    IoHwAbs_CapSense_Init();


    

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
            IoHwAbs_Light_Off();
        }
        else if (IoHwAbs_CapSense_Get_Button1_State())
        {
            IoHwAbs_Light_On();
        }
        else
        {

        }

        if (IoHwAbs_CapSense_Get_Slider_State(&brightness))
        {
            IoHwAbs_Light_Set_Brightness(brightness);
        }

        

    }
}

void Low_Prio_Task(void* param)
{
    TickType_t xLastWakeTime_Low_Prio;

    static volatile int16_t Mic_value;

    (void)param;

    IoHwAbs_Mic_Init();
    
    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime_Low_Prio = xTaskGetTickCount ();
    for (;;)
    {
        // Wait for the next cycle.
        (void)xTaskDelayUntil( &xLastWakeTime_Low_Prio, LOW_PRIO_TASK_PERIODICITY );

        Mic_value = IoHwAbs_Mic_Get_Current_Value();

    }
}
