#include "chip_control.h"
#include "ltc2943.h"
#include "ltc2943_reg.h"


// Function to perform the LTC2943 I2C Read Protocol 
static bool ChipControl_ReadRegister(uint8_t regAddress, uint8_t *dataBuff, uint8_t dataSize)
{
    bool flag = false;

    if(LTC2943_Write(LTC2943_ADDRESS, &regAddress, LTC2943_REG_ADDRESS_SIZE))
    {
        if(LTC2943_Read(LTC2943_ADDRESS, dataBuff, dataSize))
        {
            flag = true;
        }else{}
    }else{}

    return flag;
}

// Function to perform the LTC2943 I2C Write Protocol
static bool ChipControl_WriteRegister(uint8_t regAddress, uint8_t *dataBuff, uint8_t dataSize)
{
    bool flag = false;
    uint8_t const buffSize = dataSize + LTC2943_REG_ADDRESS_SIZE;
    uint8_t writeBuff[10]; 
    writeBuff[0] = regAddress;

    memcpy(&(writeBuff[1]), dataBuff, dataSize);

    if(LTC2943_Write(LTC2943_ADDRESS, writeBuff, buffSize))
    {
        flag = true;
    }else{}

    return flag;
}

// Function to get the corresponding prescaler M value (Refere to LTC2943 datasheet)
static uint16_t ChipControl_ConvertPrescaler(uint8_t prescalerValue_M)
{
    uint16_t prescaler_M;

    switch(prescalerValue_M)
    {
        case 0:
            prescaler_M = 1;
           break;
        case BIT(3):
            prescaler_M = 4;
           break;
        case BIT(4):
            prescaler_M = 16;
           break;
        case (BIT(3)|BIT(4)):
            prescaler_M = 64;
           break;
        case BIT(5):
            prescaler_M = 256;
           break;
        case (BIT(3)|BIT(5)):
            prescaler_M = 1024;
           break;
        case (BIT(4)|BIT(5)):
        case (BIT(3)|BIT(4)|BIT(5)):
            prescaler_M = 4096;
           break;
        default:
            prescaler_M = 4096;
           break;            
    }

    return prescaler_M;
}

/// @brief Read the ADC mode from the appropriate register and store it in the 'mode' variable
/// @param mode pointer to ADC mode value
/// @return true if the operation is successful, false otherwise
bool ChipControl_GetADCMode(uint8_t* mode)
{
    uint8_t adcMode;

    if(!ChipControl_ReadRegister(LTC2943_CONTROL_REG_B, &adcMode, LTC2943_REG_ADDRESS_SIZE))
    {
        // Error reading ADC mode
        return false;
    }else{}

    // Extract the current ADC mode from the control register B, located in bits [7:6]
    adcMode = ((adcMode & (uint8_t)CONTROL_REG_ADC_MODE_MASK) >> (uint8_t)CONTROL_REG_ADC_MODE_POSITION);
    *mode = adcMode;

    return true;
}

/// @brief Change the ADC mode on the LTC2943 chip
/// @param mode ADC mode new value (automatic, scan, manual or sleep)
/// @return true if the write operation is successful, false otherwise
bool ChipControl_SetADCMode(uint8_t mode)
{
    uint8_t currentRegB;
    uint8_t newRegB;

    if(!ChipControl_ReadRegister(LTC2943_CONTROL_REG_B, &currentRegB, LTC2943_REG_ADDRESS_SIZE))
    {
        // Error reading Control Register (B)
        return false;
    }else{}

    // clear bits [7:6] current mode
    newRegB = (currentRegB & ~(CONTROL_REG_ADC_MODE_MASK));

    // set bits [7:6] to new mode
    newRegB = (newRegB | (mode << (uint8_t)CONTROL_REG_ADC_MODE_POSITION));

    if(!ChipControl_WriteRegister(LTC2943_CONTROL_REG_B, &newRegB, LTC2943_REG_ADDRESS_SIZE))
    {
        // Error writing ADC mode
        return false;
    }else{}

    return true;
}

/// @brief Check if there is a temperature alert on the LTC2943 chip
/// @return true if there is a temperature alert, false otherwise
bool ChipControl_CheckTemperatureAlert(void)
{
    uint8_t currentStatus;

    if(!ChipControl_ReadRegister(LTC2943_STATUS_REG_A, &currentStatus, LTC2943_REG_ADDRESS_SIZE))
    {
        // Error reading status register
        return false;
    }else{}
    
    // Check if temperature alert bit is set
    if((currentStatus & STATUS_REG_TEMPERATURE_ALERT_BIT_4))
    {
        return true;
    }else{
        return false;
    }
    
}

/// @brief Set the charge thresholds on the LTC2943 chip
/**
 *  Convert charge (mAh) to registers (E, F, G, H), where
 *  qLSB = charge * 0.34 * (50 / RSENSE) * (prescaler_M / 4096) 
 *  (Refere to LTC2943 datasheet)
 */
/// @param minThreshold Charge Threshold Low G,H
/// @param maxThreshold Charge Threshold High E,F
/// @return true if the write operations are successful, false otherwise
bool ChipControl_SetChargeThresholds(float minThreshold, float maxThreshold)
{
    uint32_t registerValue;
    uint16_t prescaler_M;
    uint8_t currentRegB;
    uint8_t writeBuff[4];
    uint8_t *tmpPtr;

    // Read Control Register (B)
    if(!ChipControl_ReadRegister(LTC2943_CONTROL_REG_B, &currentRegB, LTC2943_REG_ADDRESS_SIZE))
    {
        // Error reading Control Register (B)
        return false;
    }else{}

    // Get coulomb counter prescaling factor M
    currentRegB &= CONTROL_REG_PRESCALER_M_MASK;
    prescaler_M = ChipControl_ConvertPrescaler(currentRegB);

    // Calculate register value for charge maximum threshold
    registerValue = maxThreshold * (0.34 * 50 / R_SENSE) * (prescaler_M / 4096);

    if(registerValue > MAX_THRESHOLD)
    {
        registerValue = MAX_THRESHOLD;
    }else{}

    // Set Charge Threshold High E,F (MSB, LSB) (big indian)
    tmpPtr = (uint8_t*)&registerValue;
    registerValue &= 0xFFFF; 
    writeBuff[0] = tmpPtr[1];
    writeBuff[1] = tmpPtr[0];

    // Calculate register value for charge minimum threshold
    registerValue = minThreshold * (0.34 * 50 / R_SENSE) * (prescaler_M / 4096);

    if(registerValue > MAX_THRESHOLD)
    {
        registerValue = MAX_THRESHOLD;
    }else{}

    // Set Charge Threshold Low G,H (MSB, LSB) (big indian)
    registerValue &= 0xFFFF; 
    writeBuff[2] = tmpPtr[1];
    writeBuff[3] = tmpPtr[0];

    // Write the 'maxThreshold' and 'minThreshold' values sequentially to the appropriate registers
    if(!ChipControl_WriteRegister(LTC2943_CHARGE_THRESHOLD_HIGH_MSB_REG_E, writeBuff, 4))
    {
        // Error writing Charge Threshold registers
        return false;
    }else{}

    return true;    
}

/// @brief Reads the charge thresholds from the LTC2943 chip
/**
 *  Convert reading from registers (E, F, G, H) to charge (mAh) , where
 *  charge = qLSB / ((0.34 * (50 / RSENSE) * (prescaler_M / 4096)) 
 *  (Refere to LTC2943 datasheet)
 */
/// @param minThreshold pointer to Charge Threshold Low G,H
/// @param maxThreshold 
/// @return true the operation is successful, false otherwise
bool ChipControl_GetChargeThresholds(float* minThreshold, float* maxThreshold)
{
    uint16_t regMinthreshold;
    uint16_t regMaxthreshold;
    uint16_t prescaler_M;
    uint8_t ChargeThresholdData[4];
    uint8_t currentRegB;

    // Read Control Register (B)
    if(!ChipControl_ReadRegister(LTC2943_CONTROL_REG_B, &currentRegB, LTC2943_REG_ADDRESS_SIZE))
    {
        // Error reading Control Register (B)
        return false;
    }else{}

    // Get coulomb counter prescaling factor M
    currentRegB &= CONTROL_REG_PRESCALER_M_MASK;
    prescaler_M = ChipControl_ConvertPrescaler(currentRegB);

    // Read the 'maxThreshold' and 'minThreshold' values sequentially from the appropriate registers
    if(!ChipControl_ReadRegister(LTC2943_CHARGE_THRESHOLD_HIGH_MSB_REG_E, ChargeThresholdData, 4))
    {
        // Error reading Charge Threshold registers
        return false;
    }else{}

    regMaxthreshold = (ChargeThresholdData[0] << 8) | ChargeThresholdData[1];
    regMinthreshold = (ChargeThresholdData[2] << 8) | ChargeThresholdData[3];

    *maxThreshold = regMaxthreshold / ((0.34 * 50 / R_SENSE) * (prescaler_M / 4096));
    *minThreshold = regMinthreshold / ((0.34 * 50 / R_SENSE) * (prescaler_M / 4096));
    return true;
}


/// @brief Check that the charge is within thresholds
/**
 *  Convert reading from registers (C, D) to charge (mAh) , where
 *  charge = qLSB / ((0.34 * (50 / RSENSE) * (prescaler_M / 4096)) 
 *  (Refere to LTC2943 datasheet)
 */
/// @return Return true if the charge is within the thresholds, false otherwise
bool ChipControl_CheckChargeWithinThresholds(void)
{
    uint16_t regCharge;
    uint16_t prescaler_M;
    float minThreshold;
    float maxThreshold;
    double charge;
    uint8_t currentRegB;
    uint8_t chargeData[2];
    
    // Read Control Register (B)
    if(!ChipControl_ReadRegister(LTC2943_CONTROL_REG_B, &currentRegB, LTC2943_REG_ADDRESS_SIZE))
    {
        // Error reading Control Register (B)
        return false;
    }else{}

    // Get coulomb counter prescaling factor M
    currentRegB &= CONTROL_REG_PRESCALER_M_MASK;
    prescaler_M = ChipControl_ConvertPrescaler(currentRegB);

    // Read the charge value from the appropriate register
    if(!ChipControl_ReadRegister(LTC2943_ACC_CHARGE_MSB_REG_C, chargeData, 2))
    {
        // Error reading Charge data registers
        return false;
    }else{}
    
    regCharge = (chargeData[0] << 8) | chargeData[1];
    charge = regCharge / ((0.34 * 50 / R_SENSE) * (prescaler_M / 4096));

    // Retrieve charge thresholds
    if (!ChipControl_GetChargeThresholds(&minThreshold, &maxThreshold))
    {
        // Error getting charge thresholds
        return false;
    }

    // Check if charge is within thresholds
    bool isWithinThresholds = (charge >= minThreshold) && (charge <= maxThreshold);
    
    return isWithinThresholds;
}
