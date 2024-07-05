/*
 * LDR_Prog.c
 *
 *  Created on: Jul 4, 2024
 *      Author: samar ibrahim
 */

#include "../../LIB/stdTypes.h"
#include "../../LIB/Error_States.h"

#include "../../MCAL/DIO/DIO_int.h"
#include "../../MCAL/ADC/ADC_Config.h"
#include "../../MCAL/ADC/ADC_int.h"
#include "../../MCAL/GIE/GIE_int.h"
#include "LDR_config.h"
#include "LDR_priv.h"
#include "../LCD/LCD_int.h"
#include <util/delay.h>

#define REFERENCE_VOLTAGE   5000UL  // 5V reference voltage in millivolts
#define FIXED_RESISTOR      10000UL // Fixed resistor value in ohms
void LDR_vidReadADCValue(void *Copy_PvidLDRVOLT);
static volatile u16 ADCValue = 0;

ES_t LDR_enuInit(LDR_t* Copy_PstrLDRconfig) {
    ES_t Local_enuErrorState = ES_NOK;

    // Initialize ADC and enable interrupts
    ADC_enuInit();
    ADC_enuEnableInterrupt();
    ADC_enuCallBack(LDR_vidReadADCValue, &ADCValue);
    GIE_enuGloable_Interrupt_Enable();

    // Iterate through each LDR configuration
    for (u8 Local_u8Iterator = 0; Local_u8Iterator < LDRNUM; Local_u8Iterator++) {
        if (Copy_PstrLDRconfig[Local_u8Iterator].LDR_Channel != NOTCONNECTED) {
            // Set pin direction and select ADC channel
            DIO_enuSetPinDirection(DIO_u8PORTA, Copy_PstrLDRconfig[Local_u8Iterator].LDR_Channel, DIO_u8INPUT);
            ADC_enuSelectChannel(Copy_PstrLDRconfig[Local_u8Iterator].LDR_Channel);
        }
    }

    ADC_enuEnable();
    return Local_enuErrorState;
}

void LDR_vidReadADCValue(void *Copy_PvidLDRVOLT) {
    if (Copy_PvidLDRVOLT != NULL) {
        ADC_enuReadADCValue(Copy_PvidLDRVOLT);
    }
}

ES_t LDR_enuGetValue(u8 Copy_u8_LDR_ID, u16 *Copy_u16Value) {
    ES_t Local_enuErrorState = ES_NOK;

    if (Copy_u16Value != NULL) {
        // Start ADC conversion
        ADC_enuStartConversion();



        *Copy_u16Value = ADCValue;

        Local_enuErrorState = ES_OK;
    }

    return Local_enuErrorState;
}

