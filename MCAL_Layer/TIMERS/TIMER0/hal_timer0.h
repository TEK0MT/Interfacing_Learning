/* 
 * File:   hal_timer0.h
 * Author: Mohamed Tarek
 *
 * Created on August 13, 2024, 3:36 AM
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H
/*Section : includes */
#include "../../GPIO/hal_gpio.h"
#include "../../Interrupt/mcal_interrupt_manager.h"
#include "../../Interrupt/mcal_internal_interrupt.h"
/* Section : Macro Declarations */
#define TIMER0_16BIT  1
#define TIMER0_8BIT  0

#define TRM_PRESCALER_ON  1
#define TRM_PRESCALER_OFF  0

#define TIMER0_TIMER_MODE       1
#define TIMER0_COUNTER_MODE     0

#define TIMER0_RISING_EDGE_SELECT      1
#define TIMER0_FALLING_EDGE_SELECT      0
/* Section : Macro Functions Declarations */
#define TIMER0_ENABLE()     (T0CONbits.TMR0ON = 1)
#define TIMER0_DISABLE()     (T0CONbits.TMR0ON = 0)


#define TIMER0_8BIT_MODE()  (T0CONbits.T08BIT = 1)
#define TIMER0_16BIT_MODE()  (T0CONbits.T08BIT = 0)

#define INTERNAL_CLOCK()      (T0CONbits.T0CS = 0)
#define EXTERNAL_PIN_CLOCK()      (T0CONbits.T0CS = 1)

#define TIMER0_RISING_EDGE()        (T0CONbits.T0SE = 0)
#define TIMER0_FALLING_EDGE()        (T0CONbits.T0SE = 1)

#define TIMER0_PRESCALER_ON()       (T0CONbits.PSA = 0)
#define TIMER0_PRESCALER_OFF()       (T0CONbits.PSA = 1)
/* Section : Data Type Declarations */
typedef enum{
    PRESCALER_DIV_2 = 0,
            PRESCALER_DIV_4,
            PRESCALER_DIV_8,
            PRECALER_DIV_16,
            PRESCALER_DIV_32,
            PRESCALER_DIV_64,
            PRESCALER_DIV_128,
            PRESCALER_DIV_256
}prescaler_value_t;


typedef struct{
#if TIMER0_INTERRUPT
    void (* TIMER0_HANDLER)(void);
#if INETRRUPT_PRIORITY
    
    interrupt_priority priority;
#endif
#endif
    uint8 mode :1;
    uint8 size :1;
    uint16 prevalue;
    uint8 edge :1;
    uint8 prescaler;
    prescaler_value_t prescaler_val;
}timer0_t;

/* Section : Function Declarations */
std_ReturnType TIMER0_INIT(const timer0_t *timer);
std_ReturnType TIMER0_DEINIT(const timer0_t *timer);
std_ReturnType TIMER0_Write_Value(const timer0_t *timer,uint16 var);
std_ReturnType TIMER0_Read_Value(const timer0_t *timer,uint16 *var);

#endif	/* HAL_TIMER0_H */

