/*
 * LDR_Config.c
 *
 *  Created on: Jul 4, 2024
 *      Author: user
 */

#include "../../MCAL/ADC/ADC_int.h"
#include "LDR_Config.h"

#include "LDR_config.h"

// Initialize the LDR_Config array with the correct structure
LDR_t LDR_Config[LDRNUM] = {
    { 0 } , // Assuming the LDR is connected to ADC channel 0
};
