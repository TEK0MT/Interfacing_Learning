/* 
 * File:   hal_cpp.h
 * Author: Mohamed Tarek
 *
 * Created on August 23, 2024, 7:04 AM
 */

#ifndef HAL_CPP_H
/*Section : includes */
#include "pic18f4620.h"
#include "../std_libraries.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../GPIO/hal_gpio.h"
#include "ccp_cfg.h"
/* Section : Macro Declarations */
#define CCP_PWM_COMPARE_CAPTURE_DISABLE  ((uint8)0x00)
#define CCP_COMPARE  ((uint8)0x02)
#define CCP_CAPTURE_FAILING_EDGE  ((uint8)0x04)
#define CCP_CAPTURE_RISING_EDGE  ((uint8)0x05)
#define CCP_CAPTURE_RISING_EDGE  ((uint8)0x05)
#define CCP_CAPTURE_ON_4TH_RISING_EDGE  ((uint8)0x06)
#define CCP_CAPTURE_ON_16TH_RISING_EDGE  ((uint8)0x07)
#define CCP_COMPARE_PIN_GPIO_HIGH  ((uint8)0x08)
#define CCP_COMPARE_PIN_GPIO_LOW  ((uint8)0x09)
#define CCP_COMPARE_GEN_INTERRUPT  ((uint8)0x0A)
#define CCP_COMPARE_SPECIAL_EVENT  ((uint8)0x0B)
#define CCP_PWM  ((uint8)0x0C)


#define CCP_CAPTURE_NOT_READY 0x00
#define CCP_CAPTURE_READY     0x01


#define TIMER2_CCP_POSTSCALER_DIV_BY_1       1
#define TIMER2_CCP_POSTSCALER_DIV_BY_2       2
#define TIMER2_CCP_POSTSCALER_DIV_BY_3       3
#define TIMER2_CCP_POSTSCALER_DIV_BY_4       4
#define TIMER2_CCP_POSTSCALER_DIV_BY_5       5
#define TIMER2_CCP_POSTSCALER_DIV_BY_6       6
#define TIMER2_CCP_POSTSCALER_DIV_BY_7       7
#define TIMER2_CCP_POSTSCALER_DIV_BY_8       8
#define TIMER2_CCP_POSTSCALER_DIV_BY_9       9
#define TIMER2_CCP_POSTSCALER_DIV_BY_10      10
#define TIMER2_CCP_POSTSCALER_DIV_BY_11      11
#define TIMER2_CCP_POSTSCALER_DIV_BY_12      12
#define TIMER2_CCP_POSTSCALER_DIV_BY_13      13
#define TIMER2_CCP_POSTSCALER_DIV_BY_14      14
#define TIMER2_CCP_POSTSCALER_DIV_BY_15      15
#define TIMER2_CCP_POSTSCALER_DIV_BY_16      16


#define TIMER2_CCP_PRESCALER_OFF   0x01
#define TIMER2_CCP_PRESCALER_DIV_4 0x02
#define TIMER2_CCP_PRESCALER_DIV_16 0x03

/* Section : Macro Functions Declarations */
#define CCP1_MODE_SELECT(CCP_MODE)  (CCP1CONbits.CCP1M = CCP_MODE)
#define CCP2_MODE_SELECT(CCP_MODE)  (CCP2CONbits.CCP2M = CCP_MODE)

/* Section : Data Type Declarations */
typedef enum{
    CCP_CAPTURE_MODE,
            CCP_COMPARE_MODE,
            CCP_PWM_MODE
}ccp_mode_t;


typedef enum{
    CCP1_INST = 0,
            CCP2_INST
}ccp_inst;

typedef union{
    struct{
    uint8 ccp_lval;
    uint8 ccp_hval;
    };
    struct{
        uint16 value;
    };
}CCP_REG_T;


typedef enum{
    CCP1_CCP2_TIMER3 = 0,
            CCP1_TIMER1_CCPN2_TIMER2,
            CCP1_CCP2_TIMER1
}ccp_capture_timer_t;

typedef struct{
    ccp_inst ccpx;
    ccp_mode_t mode;
    uint8 variant;
    pin_config_t pin;
    ccp_capture_timer_t timer;
#if (CCP1_GEN_MODE_SELECT == CCP_PWM_GEN_MODE)  || (CCP2_GEN_MODE_SELECT == CCP_PWM_GEN_MODE)
    uint32 pwm_freq;
    uint8 timer2_postscaler;
    uint8 timer2_pre_scaler;
#endif
#if CCP1_INTERRUPT == INTERRUPT_ENABLED
    void (*Interrupt_CCP1_Handler)(void);
    interrupt_priority ccp1_priority;
#endif
#if CCP2_INTERRUPT == INTERRUPT_ENABLED
    void (*Interrupt_CCP2_Handler)(void);
    interrupt_priority ccp2_priority;
#endif
    
}ccp_t;

/* Section : Function Declarations */
std_ReturnType CCP_Init(const ccp_t* ccp);
std_ReturnType CCP_DeInit(const ccp_t* ccp);
#if CCP1_GEN_MODE_SELECT == CCP_CAPTURE_GEN_MODE
std_ReturnType CCP_IsCaptureReady(uint8 *status);
std_ReturnType CCP_Capture_Mode_Read_Value(uint16 *value);
#endif
#if CCP1_GEN_MODE_SELECT == CCP_COMPARE_GEN_MODE
std_ReturnType CCP_IsCompareReady(uint8 *status);
std_ReturnType CCP_Compare_Set_Value(const ccp_t* ccp,uint16 value);
#endif
#if (CCP1_GEN_MODE_SELECT == CCP_PWM_GEN_MODE) || (CCP2_GEN_MODE_SELECT == CCP_PWM_GEN_MODE)
std_ReturnType CCP_PWM_Set_Duty(const ccp_t* ccp,uint8 val);
std_ReturnType CCP_PWM_Start(const ccp_t* ccp);
std_ReturnType CCP_PWM_Stop(const ccp_t* ccp);
#endif
#endif	/* HAL_CPP_H */

