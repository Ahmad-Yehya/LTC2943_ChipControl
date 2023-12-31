#ifndef CHIP_CONTROL_H
#define CHIP_CONTROL_H

#include <stdbool.h>
#include <stdint.h>
#include <string.h>



#define R_SENSE                     50.0F   // default value for sense resistor (50.0 mΩ)
#define MAX_THRESHOLD               0xFFFF  // Maximum threshold value


// ChipControl API function prototypes

bool ChipControl_GetADCMode(uint8_t *mode);

bool ChipControl_SetADCMode(uint8_t mode);

bool ChipControl_CheckTemperatureAlert(void);

bool ChipControl_SetChargeThresholds(float minThreshold, float maxThreshold);

bool ChipControl_CheckChargeWithinThresholds(void);

#endif /* CHIP_CONTROL_H */