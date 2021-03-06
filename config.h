#ifndef CONFIG_H
#define CONFIG_H

#include "lpc134x.h"

#define CFG_PI                      (3.141)

// This doesn't actually effect clock speed
#define CFG_CPU_CCLK                (72000000)

#define CFG_PWM_DEFAULT_PULSEWIDTH  (CFG_CPU_CCLK / 1000)
#define CFG_PWM_DEFAULT_DUTYCYCLE   (50)

#define CFG_UART_BAUDRATE           (9600)
#define CFG_UART_BUFSIZE            (512)

#define CFG_CTL_K_PREDICT           (10)
#define CFG_CTL_K_UPDATE            (2)

#define CFG_GYRO_UPDATE_MSECS      (5) // msecs between sensor updates
#define CFG_RESPONSE_UPDATE_MSECS  (16) // msecs between responding to state
#define CFG_STATE_OUTPUT_MSECS     (700)

#define CFG_GYRO_BIAS_N_SAMPLES      500

#define CFG_ESC_CNT                  4
#define CFG_MOTOR_CNT                CFG_ESC_CNT
#define CFG_MOTOR_MAX_THRUST         20000
#define CFG_MOTOR_MIN_THRUST         36000
#define CFG_MOTOR_DEFAULT_DUTY_CYCLE 0
#define CFG_MOTOR_MAX                100

#define CFG_I2C_TIMEOUT              2

#define MOTOR_LF 1
#define MOTOR_LR 0
#define MOTOR_RF 2
#define MOTOR_RR 3

#endif
