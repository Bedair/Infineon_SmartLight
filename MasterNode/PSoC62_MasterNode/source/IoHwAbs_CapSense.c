/**********************************************************************
* File Name : IoHwAbs_CapSense.c
* 
* Description : source file for the component responsible for abstracting
*               the CapSense Driver
*
* Author : Mohamed Bedair
*
* Date : 01 Oct 2023
*
**********************************************************************/

/**********************************************************************
*                            Macro Section                            *
**********************************************************************/

#include "IoHwAbs_CapSense.h"

#include "cybsp.h"
#include "cyhal.h"
#include "cycfg.h"
#include "cycfg_capsense.h"


#define CAPSENSE_INTERRUPT_PRIORITY    (7u)

/**********************************************************************
*                           Local Functions                           *
**********************************************************************/
static void CapSense_ISR(void);


static void CapSense_ISR(void)
{
    Cy_CapSense_InterruptHandler(CYBSP_CSD_HW, &cy_capsense_context);
}

/**********************************************************************
*                          Global Variables                           *
**********************************************************************/
cyhal_ezi2c_slave_cfg_t sEzI2C_sub_cfg;
cyhal_ezi2c_cfg_t sEzI2C_cfg;
cyhal_ezi2c_t sEzI2C;

/**********************************************************************
*                          Global Functions                           *
**********************************************************************/
/*
* Funcation Name : IoHwAbs_CapSense_Init
* Description    : Used to initialize the CapSense module
* Parameters     : NA
* Return         : NA
*/
void IoHwAbs_CapSense_Init(void)
{
    uint32_t status = CYRET_SUCCESS;

    /* CapSense interrupt configuration parameters */
    static const cy_stc_sysint_t capSense_intr_config =
    {
        .intrSrc = csd_interrupt_IRQn,
        .intrPriority = CAPSENSE_INTERRUPT_PRIORITY,
    };

    /*Initialize CapSense Data structures */
    status = Cy_CapSense_Init(&cy_capsense_context);
    if(CY_RET_SUCCESS != status)
    {
        CY_ASSERT(0u);
    }

    /* Initialize CapSense interrupt */
    cyhal_system_set_isr(csd_interrupt_IRQn, csd_interrupt_IRQn, CAPSENSE_INTERRUPT_PRIORITY, &CapSense_ISR);
    NVIC_ClearPendingIRQ(capSense_intr_config.intrSrc);
    NVIC_EnableIRQ(capSense_intr_config.intrSrc);

    
    /* Initialize the CapSense firmware modules. */
    status = Cy_CapSense_Enable(&cy_capsense_context);
    if(CY_RET_SUCCESS != status)
    {
        CY_ASSERT(0u);
    }
}


/*
* Funcation Name : IoHwAbs_CapSense_Tuner_Init
* Description    : Used to initialize the CapSense tuner
* Parameters     : NA
* Return         : NA
*/
void IoHwAbs_CapSense_Tuner_Init(void)
{
    cy_rslt_t result;
    /* Configure Capsense Tuner as EzI2C Slave */
    sEzI2C_sub_cfg.buf = (uint8 *)&cy_capsense_tuner;
    sEzI2C_sub_cfg.buf_rw_boundary = sizeof(cy_capsense_tuner);
    sEzI2C_sub_cfg.buf_size = sizeof(cy_capsense_tuner);
    sEzI2C_sub_cfg.slave_address = 8U;

    sEzI2C_cfg.data_rate = CYHAL_EZI2C_DATA_RATE_400KHZ;
    sEzI2C_cfg.enable_wake_from_sleep = true;
    sEzI2C_cfg.slave1_cfg = sEzI2C_sub_cfg;
    sEzI2C_cfg.sub_address_size = CYHAL_EZI2C_SUB_ADDR16_BITS;
    sEzI2C_cfg.two_addresses = false;
    result = cyhal_ezi2c_init( &sEzI2C, CYBSP_I2C_SDA, CYBSP_I2C_SCL, NULL, &sEzI2C_cfg);
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0u);
    }
}

/*
* Funcation Name : IoHwAbs_CapSense_Tuner_Update
* Description    : Used to send new measured values to the Tuner
* Parameters     : NA
* Return         : NA
*/
void IoHwAbs_CapSense_Tuner_Update(void)
{
    Cy_CapSense_RunTuner(&cy_capsense_context);
}


/*
* Funcation Name : IoHwAbs_CasSense_Start_Scan
* Description    : Used to start new CapSense measurement
* Parameters     : NA
* Return         : NA
*/
void IoHwAbs_CasSense_Start_Scan(void)
{
    Cy_CapSense_ScanAllWidgets(&cy_capsense_context);
}


/*
* Funcation Name : IoHwAbs_CapSense_Process
* Description    : Used to process the last CapSense scan results
* Parameters     : NA
* Return         : NA
*/
void IoHwAbs_CapSense_Process(void)
{
    Cy_CapSense_ProcessAllWidgets(&cy_capsense_context);
}


/*
* Funcation Name : IoHwAbs_CapSense_Scan_Done
* Description    : Used to check if the current CapSense scan is done or not
* Parameters     : NA
* Return         : whether Scan is done or not
*/
CapSense_Scan_State IoHwAbs_CapSense_Scan_Done(void)
{
    return (!Cy_CapSense_IsBusy(&cy_capsense_context));
}


/*
* Funcation Name : IoHwAbs_CapSense_Get_Button0_State
* Description    : Used to return the status of Button 0
* Parameters     : NA
* Return         : Button 0 Status
*/
CapSense_Button_State IoHwAbs_CapSense_Get_Button0_State(void)
{
    uint32_t button0_status = 0;
    

     /* Get button 0 status */
    button0_status = Cy_CapSense_IsSensorActive(
        CY_CAPSENSE_BUTTON0_WDGT_ID,
        CY_CAPSENSE_BUTTON0_SNS0_ID,
        &cy_capsense_context);

    
    return (button0_status? e_CapSense_Button_Pressed:e_CapSense_Button_Released);

}


/*
* Funcation Name : IoHwAbs_CapSense_Get_Button1_State
* Description    : Used to return the status of Button 1
* Parameters     : NA
* Return         : Button 1 Status
*/
CapSense_Button_State IoHwAbs_CapSense_Get_Button1_State(void)
{
    uint32_t button1_status = 0;

    /* Get button 1 status */
    button1_status = Cy_CapSense_IsSensorActive(
        CY_CAPSENSE_BUTTON1_WDGT_ID,
        CY_CAPSENSE_BUTTON1_SNS0_ID,
        &cy_capsense_context);
    
    return (button1_status? e_CapSense_Button_Pressed:e_CapSense_Button_Released);
}


/*
* Funcation Name : IoHwAbs_CapSense_Get_Slider_State
* Description    : Used to retuen the if the Slider is presssed 
*                  and position of the slider
* Parameters     : Pointer to the touched slider position (0 : 100)
* Return         : Current Slider value
*/
CapSense_Button_State IoHwAbs_CapSense_Get_Slider_State(uint8_t *pos)
{   
    uint16_t slider_pos = 0;
    uint8_t slider_touched = 0;
    cy_stc_capsense_touch_t *slider_touch;


    /* Get slider status */
    slider_touch = Cy_CapSense_GetTouchInfo(
        CY_CAPSENSE_LINEARSLIDER0_WDGT_ID,
        &cy_capsense_context);


    slider_pos = slider_touch->ptrPosition->x;
    slider_touched = slider_touch->numPosition;

    *pos = (slider_pos * 100) / cy_capsense_context.ptrWdConfig[CY_CAPSENSE_LINEARSLIDER0_WDGT_ID].xResolution;;
    return (slider_touched?e_CapSense_Button_Pressed:e_CapSense_Button_Released);
}
