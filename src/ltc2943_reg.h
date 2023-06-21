#ifndef LTC2943_CFG_H
#define LTC2943_CFG_H


#define BIT(x)	((uint8_t)(1) << (x))

// LTC2943 I2C address
#define LTC2943_ADDRESS                             0b1100100

// Size of register's address
#define LTC2943_REG_ADDRESS_SIZE                    0x01U

// register map
#define LTC2943_STATUS_REG_A                        0x00U
#define LTC2943_CONTROL_REG_B                       0x01U

#define LTC2943_ACC_CHARGE_MSB_REG_C                0x02U
#define LTC2943_ACC_CHARGE_LSB_REG_D                0x03U
#define LTC2943_CHARGE_THRESHOLD_HIGH_MSB_REG_E     0x04U
#define LTC2943_CHARGE_THRESHOLD_HIGH_LSB_REG_F     0x05U
#define LTC2943_CHARGE_THRESHOLD_LOW_MSB_REG_G      0x06U
#define LTC2943_CHARGE_THRESHOLD_LOW_LSB_REG_H      0x07U

#define LTC2943_VOLTAGE_MSB_REG_I                   0x08U
#define LTC2943_VOLTAGE_LSB_REG_J                   0x09U
#define LTC2943_VOLTAGE_THRESHOLD_HIGH_MSB_REG_K    0x0AU
#define LTC2943_VOLTAGE_THRESHOLD_HIGH_LSB_REG_L    0x0BU
#define LTC2943_VOLTAGE_THRESHOLD_LOW_MSB_REG_M     0x0CU
#define LTC2943_VOLTAGE_THRESHOLD_LOW_LSB_REG_N     0x0DU

#define LTC2943_CURRENT_MSB_REG_O                   0x0EU
#define LTC2943_CURRENT_LSB_REG_P                   0x0FU
#define LTC2943_CURRENT_THRESHOLD_HIGH_MSB_REG_Q    0x10U
#define LTC2943_CURRENT_THRESHOLD_HIGH_LSB_REG_R    0x11U
#define LTC2943_CURRENT_THRESHOLD_LOW_MSB_REG_S     0x12U
#define LTC2943_CURRENT_THRESHOLD_LOW_LSB_REG_T     0x13U

#define LTC2943_TEMPERATURE_MSB_REG_U               0x14U
#define LTC2943_TEMPERATURE_LSB_REG_V               0x15U
#define LTC2943_TEMPERATURE_THRESHOLD_HIGH_REG_W    0x16U
#define LTC2943_TEMPERATURE_THRESHOLD_LOW_REG_X     0x17U

// Status register REG_A flags
#define STATUS_REG_CURRENT_ALERT_BIT_6              BIT(6)
#define STATUS_REG_ACC_CHARGE_OVER_UNDER_FLOW_BIT_5 BIT(5)
#define STATUS_REG_TEMPERATURE_ALERT_BIT_4          BIT(4)
#define STATUS_REG_CHARGE_ALERT_HIGH_BIT_3          BIT(3)
#define STATUS_REG_CHARGE_ALERT_HIGH_BIT_2          BIT(2)
#define STATUS_REG_VOLTAGE_ALERT_BIT_1              BIT(1)
#define STATUS_REG_UNDERVOLTAGE_LOCKOUT_ALERT_BIT_0 BIT(0)

// Control register REG_B fields
#define CONTROL_REG_ADC_MODE_POSITION               6U
#define CONTROL_REG_ADC_MODE_MASK                   0b11000000

#define CONTROL_REG_PRESCALER_M_POSITION            3U
#define CONTROL_REG_PRESCALER_M_MASK                0b00111000

// ADC mode definitions
#define ADC_MODE_SLEEP                              0x00U
#define ADC_MODE_MANUAL                             0x01U
#define ADC_MODE_SCAN                               0x02U
#define ADC_MODE_AUTOMATIC                          0x03U

#endif /* LTC2943_CFG_H */