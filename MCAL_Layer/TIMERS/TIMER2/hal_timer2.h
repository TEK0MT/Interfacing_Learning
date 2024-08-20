/* 
 * File:   hal_timer2.h
 * Author: Mohamed Tarek
 *
 * Created on August 20, 2024, 6:36 AM
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H
/*Section : includes */
#include "../../GPIO/hal_gpio.h"
#include "../../Interrupt/mcal_interrupt_manager.h"
#include "../../Interrupt/mcal_internal_interrupt.h"
/* Section : Macro Declarations */
#define TIMER2_POSTSCALER_DIV_BY_1       0
#define TIMER2_POSTSCALER_DIV_BY_2       1
#define TIMER2_POSTSCALER_DIV_BY_3       2
#define TIMER2_POSTSCALER_DIV_BY_4       3
#define TIMER2_POSTSCALER_DIV_BY_5       4
#define TIMER2_POSTSCALER_DIV_BY_6       5
#define TIMER2_POSTSCALER_DIV_BY_7       6
#define TIMER2_POSTSCALER_DIV_BY_8       7
#define TIMER2_POSTSCALER_DIV_BY_9       8
#define TIMER2_POSTSCALER_DIV_BY_10      9
#define TIMER2_POSTSCALER_DIV_BY_11      10
#define TIMER2_POSTSCALER_DIV_BY_12      11
#define TIMER2_POSTSCALER_DIV_BY_13      12
#define TIMER2_POSTSCALER_DIV_BY_14      13
#define TIMER2_POSTSCALER_DIV_BY_15      14
#define TIMER2_POSTSCALER_DIV_BY_16      15



#define TIMER2_PRESCALER_OFF   0x00
#define TIMER2_PRESCALER_DIV_4 0x01
#define TIMER2_PRESCALER_DIV_16 0x03


/* Section : Macro Functions Declarations */
#define TIMER2_ENABLE()     (T2CONbits.TMR2ON = 1)
#define TIMER2_DISABLE()     (T2CONbits.TMR2ON = 0)

#define TIMER2_PRESCALER(val)             (T2CONbits.T2CKPS = val)


#define TIMER2_POSTSCALE(val)             (T2CONbits.TOUTPS = val)

/* Section : Data Type Declarations */
    typedef struct{
#if TIMER2_INTERRUPT
    void (* TIMER2_HANDLER)(void);
#if INETRRUPT_PRIORITY
    
    interrupt_priority priority;
#endif
#endif
    uint8 prevalue;
    uint8 prescaler_val;
    uint8 postscale_val;
}timer2_t;


/* Section : Function Declarations */
std_ReturnType TIMER2_INIT(const timer2_t *timer);
std_ReturnType TIMER2_DEINIT(const timer2_t *timer);
std_ReturnType TIMER2_Write_Value(const timer2_t *timer,uint8 val);
std_ReturnType TIMER2_Read_Value(const timer2_t *timer,uint8 *val);
#endif	/* HAL_TIMER2_H */

