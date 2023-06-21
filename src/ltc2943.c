#include <stdbool.h>
#include <stdint.h>
#include "ltc2943.h" 
#include "ltc2943_reg.h"


/// @brief Initialize the LTC2943 driver and I2C communication
/// @return true if the initialization is successful, false otherwise
bool LTC2943_Initialise(void)
{
    // Initialize and configure I2C driver here

    return true;
}


/// @brief Read data from the LTC2943 chip
/// @param address 
/// @param dest 
/// @param dataSize 
/// @return true if the read operation is successful, false otherwise
bool LTC2943_Read(uint8_t address, uint8_t *dest, uint8_t dataSize)
{
    // Use I2C driver's read function to read 'dataSize' bytes from the chip at 'address'

    return true;
}


/// @brief Write data to the LTC2943 chip
/// @param address 
/// @param src 
/// @param dataSize 
/// @return true if the write operation is successful, false otherwise
bool LTC2943_Write(uint8_t address, uint8_t *src, uint8_t dataSize)
{
    // Use I2C driver's write function to write 'dataSize' bytes from the 'src' buffe to the chip at 'address'

    return true;
}
