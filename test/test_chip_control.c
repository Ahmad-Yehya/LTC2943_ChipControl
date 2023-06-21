#ifdef TEST

#include "unity.h"
#include "chip_control.h"
#include "ltc2943_reg.h"
#include "ltc2943.h"
#include "mock_ltc2943.h"


void setUp(void)
{
  // setup function called before every test
}

void tearDown(void)
{
    // teardown function called after every test
}

//Test Case 0
void test_GetADCMode()
{
  uint8_t mode = ADC_MODE_SLEEP;

  LTC2943_Write_IgnoreAndReturn(true);

  LTC2943_Read_ExpectAndReturn(NULL, &mode, 1, true);
  LTC2943_Read_IgnoreArg_address();
  LTC2943_Read_IgnoreArg_dataSize();
  LTC2943_Read_ReturnThruPtr_dest(&mode);

  bool status = ChipControl_GetADCMode(&mode);
  TEST_ASSERT_TRUE(status);
  TEST_ASSERT_EQUAL_UINT8(mode, ADC_MODE_SLEEP);

}

//Test Case 1
void test_SetADCMode()
{
  uint8_t mode = ADC_MODE_MANUAL;
  uint8_t value = ADC_MODE_SLEEP;

  LTC2943_Write_IgnoreAndReturn(true);

  LTC2943_Read_ExpectAndReturn(NULL, &value, 1, true);

  LTC2943_Read_IgnoreArg_address();
  LTC2943_Read_IgnoreArg_dataSize();
  LTC2943_Read_ReturnThruPtr_dest(&value);

  bool success = ChipControl_SetADCMode(mode);
  TEST_ASSERT_TRUE(success);

}

//Test Case 2
void test_CheckTemperatureAlert()
{
  uint8_t value = 0b00010000;

  LTC2943_Write_IgnoreAndReturn(true);

  LTC2943_Read_ExpectAndReturn(NULL, &value, 1, true);
  LTC2943_Read_IgnoreArg_address();
  LTC2943_Read_IgnoreArg_dest();
  LTC2943_Read_IgnoreArg_dataSize();
  LTC2943_Read_ReturnThruPtr_dest(&value);

  bool alert = ChipControl_CheckTemperatureAlert();
  TEST_ASSERT_TRUE(alert);

}

//Test Case 3
void test_SetChargeThresholds()
{
  uint8_t M = 0b00111000;
  // uint8_t value = ADC_MODE_SLEEP;

  LTC2943_Write_IgnoreAndReturn(true);

  LTC2943_Read_ExpectAndReturn(NULL, &M, 1, true);
  LTC2943_Read_IgnoreArg_address();
  LTC2943_Read_IgnoreArg_dest();
  LTC2943_Read_IgnoreArg_dataSize();
  LTC2943_Read_ReturnThruPtr_dest(&M);

  bool success = ChipControl_SetChargeThresholds(1.5, 4.5);
  TEST_ASSERT_TRUE(success);

}

//Test Case 4
//make sure ChipControl_ConvertPrescaler is not defined static
// void test_ConvertPrescaler()
// {
//   uint8_t M = 0b00111000;
//   uint16_t value = 0;

//   value = ChipControl_ConvertPrescaler(M);

//   TEST_ASSERT_EQUAL_UINT16(value, 4096);

// }

#endif