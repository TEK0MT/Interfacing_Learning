/* 
 * File:   hal_timer1.h
 * Author: Mohamed Tarek
 *
 * Created on August 19, 2024, 3:15 AM
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H
/*Section : includes */
#include "../../GPIO/hal_gpio.h"
#include "../../Interrupt/mcal_interrupt_manager.h"
#include "../../Interrupt/mcal_internal_interrupt.h"
/* Section : Macro Declarations */
#define TIMER1_COUNTER    0x01
#define TIMER1_TIMER    0x00

#define TIMER1_16BIT_OP 0x01
#define TIMER1_8BIT_OP 0x00

#define TIMER1_PRESCALER_OFF   0x00
#define TIMER1_PRESCALER_DIV_2 0x01
#define TIMER1_PRESCALER_DIV_4 0x02
#define TIMER1_PRESCALER_DIV_8 0x03


/* Section : Macro Functions Declarations */
#define TIMER1_ENABLE()     (T1CONbits.TMR1ON = 1)
#define TIMER1_DISABLE()     (T1CONbits.TMR1ON = 0)

#define TIMER1_TIMER_MODE()     (T1CONbits.TMR1CS = 0)
#define TIMER1_COUNTER_MODE()     (T1CONbits.TMR1CS = 1)

#define TIMER1_OSC_ON()             (T1CONbits.T1OSCEN = 1)
#define TIMER1_OSC_OFF()             (T1CONbits.T1OSCEN = 0)

#define TIMER1_SYNC_CLOCK()             (T1CONbits.T1SYNC = 0)
#define TIMER1_ASYNC_CLOCK()             (T1CONbits.T1SYNC = 1)

#define TIMER1_PRESCALER(val)             (T1CONbits.T1CKPS = val)

#define TIMER1_8BIT()                       (T1CONbits.RD16 = 0)
#define TIMER1_16BIT()                       (T1CONbits.RD16 = 1)
/* Section : Data Type Declarations */
    typedef struct{
#if TIMER1_INTERRUPT
    void (* TIMER1_HANDLER)(void);
#if INETRRUPT_PRIORITY
    
    interrupt_priority priority;
#endif
#endif
    uint8 mode :1;
    uint8 size :1;
    uint16 prevalue;
    uint8 prescaler_val;
}timer1_t;


/* Section : Function Declarations */
std_ReturnType TIMER1_INIT(const timer1_t *timer);
std_ReturnType TIMER1_DEINIT(const timer1_t *timer);
std_ReturnType TIMER1_Write_Value(const timer1_t *timer,uint16 val);
std_ReturnType TIMER1_Read_Value(const timer1_t *timer,uint16 *val);
#endif	/* HAL_TIMER1_H */

