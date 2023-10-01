/**********************************************************************
* File Name : App_Tasks.c
* 
* Description : source file for the component that contain implementation
                for different OS tasks
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
    

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime_High_Prio = xTaskGetTickCount ();
    for (;;)
    {
        // Wait for the next cycle.
        (void)xTaskDelayUntil( &xLastWakeTime_High_Prio, HIGH_PRIO_TASK_PERIODICITY );

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