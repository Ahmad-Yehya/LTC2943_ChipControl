#include "build/test/mocks/mock_ltc2943.h"
#include "src/ltc2943_reg.h"
#include "src/chip_control.h"
#include "/var/lib/gems/2.7.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"








void setUp(void)

{



}



void tearDown(void)

{



}





void test_GetADCMode()

{

  uint8_t mode = 0x00U;



  LTC2943_Write_CMockIgnoreAndReturn(25, 

 1

 );



  LTC2943_Read_CMockExpectAndReturn(27, 

 ((void *)0)

 , &mode, 1, 

 1

 );

  LTC2943_Read_CMockIgnoreArg_address(28);

  LTC2943_Read_CMockIgnoreArg_dataSize(29);

  LTC2943_Read_CMockReturnMemThruPtr_dest(30, &mode, sizeof(uint8_t));



  

 _Bool 

      status = ChipControl_GetADCMode(&mode);

  do {if ((status)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(33)));}} while(0);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((mode)), (UNITY_INT)(UNITY_UINT8 )((0x00U)), (

 ((void *)0)

 ), (UNITY_UINT)(34), UNITY_DISPLAY_STYLE_UINT8);



}





void test_SetADCMode()

{

  uint8_t mode = 0x01U;

  uint8_t value = 0x00U;



  LTC2943_Write_CMockIgnoreAndReturn(44, 

 1

 );



  LTC2943_Read_CMockExpectAndReturn(46, 

 ((void *)0)

 , &value, 1, 

 1

 );



  LTC2943_Read_CMockIgnoreArg_address(48);

  LTC2943_Read_CMockIgnoreArg_dataSize(49);

  LTC2943_Read_CMockReturnMemThruPtr_dest(50, &value, sizeof(uint8_t));



  

 _Bool 

      success = ChipControl_SetADCMode(mode);

  do {if ((success)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(53)));}} while(0);



}





void test_CheckTemperatureAlert()

{

  uint8_t value = 0b00010000;



  LTC2943_Write_CMockIgnoreAndReturn(62, 

 1

 );



  LTC2943_Read_CMockExpectAndReturn(64, 

 ((void *)0)

 , &value, 1, 

 1

 );

  LTC2943_Read_CMockIgnoreArg_address(65);

  LTC2943_Read_CMockIgnoreArg_dest(66);

  LTC2943_Read_CMockIgnoreArg_dataSize(67);

  LTC2943_Read_CMockReturnMemThruPtr_dest(68, &value, sizeof(uint8_t));



  

 _Bool 

      alert = ChipControl_CheckTemperatureAlert();

  do {if ((alert)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(71)));}} while(0);



}





void test_SetChargeThresholds()

{

  uint8_t M = 0b00111000;





  LTC2943_Write_CMockIgnoreAndReturn(81, 

 1

 );



  LTC2943_Read_CMockExpectAndReturn(83, 

 ((void *)0)

 , &M, 1, 

 1

 );

  LTC2943_Read_CMockIgnoreArg_address(84);

  LTC2943_Read_CMockIgnoreArg_dest(85);

  LTC2943_Read_CMockIgnoreArg_dataSize(86);

  LTC2943_Read_CMockReturnMemThruPtr_dest(87, &M, sizeof(uint8_t));



  

 _Bool 

      success = ChipControl_SetChargeThresholds(1.5, 4.5);

  do {if ((success)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(90)));}} while(0);



}
