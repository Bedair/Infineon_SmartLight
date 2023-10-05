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
#include "cyhal_adc.h"


#define MIC_ADC_PIN             (P10_6)




/**********************************************************************
*                          Global Variables                           *
**********************************************************************/
cyhal_adc_t adc_obj;

/* ADC Channel 0 Object */
cyhal_adc_channel_t adc_chan_0_obj;

/* Default ADC configuration */
const cyhal_adc_config_t adc_config = {
        .continuous_scanning=false, // Continuous Scanning is disabled
        .average_count=1,           // Average count disabled
        .vref=CYHAL_ADC_REF_VDDA,   // VREF for Single ended channel set to VDDA
        .vneg=CYHAL_ADC_VNEG_VSSA,  // VNEG for Single ended channel set to VSSA
        .resolution = 12u,          // 12-bit resolution
        .ext_vref = NC,             // No connection
        .bypass_pin = NC };         // No connection



/* ADC channel configuration */
const cyhal_adc_channel_config_t channel_config = {
        .enable_averaging = false,  // Disable averaging for channel
        .min_acquisition_ns = 1000, // Minimum acquisition time set to 1us
        .enabled = true };          // Sample this channel when ADC performs a scan





/**********************************************************************
*                           Local Functions                           *
**********************************************************************/



/**********************************************************************
*                          Global Functions                           *
**********************************************************************/
/*
* Funcation Name : IoHwAbs_Mic_Init
* Description    : Used to initialize the interface used connect the Mic
* Parameters     : NA
* Return         : NA
*/
void IoHwAbs_Mic_Init(void)
{
    cy_rslt_t result;

    /* Initialize ADC. The ADC block which can connect to pin 10[0] is selected */
    result = cyhal_adc_init(&adc_obj, MIC_ADC_PIN, NULL);
    if(result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    /* Initialize a channel 0 and configure it to scan P10_0 in single ended mode. */
    result  = cyhal_adc_channel_init_diff(&adc_chan_0_obj, &adc_obj, MIC_ADC_PIN,
                                          CYHAL_ADC_VNEG, &channel_config);
    if(result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }


    /* Update ADC configuration */
    result = cyhal_adc_configure(&adc_obj, &adc_config);
    if(result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }
}


/*
* Funcation Name : IoHwAbs_Mic_Get_Current_Value
* Description    : Used to get the current voltage value of the mic
* Parameters     : NA
* Return         : current voltage value of the mic 
*/
int16_t IoHwAbs_Mic_Get_Current_Value(void)
{
    return (cyhal_adc_read_u16(&adc_chan_0_obj) >> 4);
}