#ifndef LTC2943_H
#define LTC2943_H

#include <stdbool.h>
#include <stdint.h>


// LTC2943 API function prototypes

bool LTC2943_Initialise(void);

bool LTC2943_Read(uint8_t address, uint8_t *dest, uint8_t dataSize);

bool LTC2943_Write(uint8_t address, uint8_t *src, uint8_t dataSize);

#endif /* LTC2943_H */