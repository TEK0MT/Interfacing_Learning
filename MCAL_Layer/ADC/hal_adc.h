/* 
 * File:   hal_adc.h
 * Author: Mohamed Tarek
 *
 * Created on August 1, 2024, 8:14 AM
 */
#ifndef HAV_ADC_H
#define	HAV_ADC_H
/*Section : includes */
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../../../../xc8/pic/include/proc/pic18f4620.h"
/* Section : Macro Declarations */
#define A0_ANALOG 0x0E
#define A1_ANALOG 0x0D
#define A2_ANALOG 0x0C
#define A3_ANALOG 0x0B
#define A4_ANALOG 0x0A
#define A5_ANALOG 0x09
#define A6_ANALOG 0x08
#define A7_ANALOG 0x07
#define A8_ANALOG 0x06
#define A9_ANALOG 0x05
#define A10_ANALOG 0x04
#define A11_ANALOG 0x03
#define A12_ANALOG 0x02
#define ALL_ANALOG 0x00
#define ALL_DIGITAL 0x0F

#define INTERNAL_ADC_VOLTAGE 0x00
#define EXTERNAL_ADC_VOLTAGE 0x01
/* Section : Macro Functions Declarations */
#define ADC_ENABLE()    (ADCON0bits.ADON = 1);
#define ADC_DISABLE()    (ADCON0bits.ADON = 0);
#define CLEAR_ADC_STATUS()  (ADCON0bits.GO_nDONE = 0); 
#define START_ADC_STATUS()  (ADCON0bits.GO_nDONE = 1); 
#define USE_INTERNAL_VOLTAGE()  do{\
                                    ADCON1bits.VCFG1 = 0;\
                                    ADCON1bits.VCFG0 = 0;\
                                    }while(0);
#define USE_EXTERNAL_VOLTAGE()  do{\
                                    ADCON1bits.VCFG1 = 1;\
                                    ADCON1bits.VCFG0 = 1;\
                                    }while(0);

/* Section : Data Type Declarations */
typedef enum{
    CHANNEL0 = 0,
            CHANNEL1,
            CHANNEL2,
            CHANNEL3,
            CHANNEL4,
            CHANNEL5,
            CHANNEL6,
            CHANNEL7,
            CHANNEL8,
            CHANNEL9,
            CHANNEL10,
            CHANNEL11,
            CHANNEL12
}SELECT_ADC_CHANNEL;


typedef enum{
    TAD0 = 0,
            TAD2,
            TAD4,
            TAD6,
            TAD8,
            TAD12,
            TAD16,
            TAD20
}ADC_ACQUISITION;

typedef enum{
    FOSC_DIV_2 = 0,
        FOSC_DIV_8,
            FOSC_DIV_32,
            FOSC_DIV_FRC,
            FOSC_DIV_4,
            FOSC_DIV_16,
            FOSC_DIV_64
}ADC_CONVERSION_TIME;

typedef enum{
    LEFT_JUSTIFIED,
            RIGHT_JUSTIFIED
}ADC_RESULT_FORMAT;

typedef struct{
    #if ADC_INTERRUPT
    void (*adc_isr)(void);
    #if INETRRUPT_PRIORITY
    interrupt_priority priority;
#endif
#endif
    ADC_CONVERSION_TIME time;
    ADC_ACQUISITION tad;
    SELECT_ADC_CHANNEL channel;
    uint8 voltage_refrence : 1;
    uint8 result_format    : 1;
    uint8 reserved         : 6;
}adc_config_t;
/* Section : Function Declarations */
std_ReturnType ADC_Init(const adc_config_t *adc );
std_ReturnType ADC_Disable(const adc_config_t *adc );
std_ReturnType ADC_Select_Channel(const adc_config_t *adc ,uint8 channels);
std_ReturnType ADC_Start_Conversion(const adc_config_t *adc);
std_ReturnType ADC_ISConversion_Done(const adc_config_t *adc ,uint8 *status);
std_ReturnType ADC_Get_Conversion_Result(const adc_config_t *adc ,uint16 *result);
std_ReturnType ADC_Get_Conversion_Blocking(const adc_config_t *adc ,SELECT_ADC_CHANNEL channel,uint16 *result);
std_ReturnType ADC_Start_Conversion_Interrupt(const adc_config_t *adc ,SELECT_ADC_CHANNEL channel);
#endif	/* HAV_ADC_H */

