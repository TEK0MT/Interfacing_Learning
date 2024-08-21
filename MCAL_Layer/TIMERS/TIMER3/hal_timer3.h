/* 
 * File:   hal_timer3.h
 * Author: Mohamed Tarek
 *
 * Created on August 21, 2024, 7:35 AM
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H
/*Section : includes */
#include "../../GPIO/hal_gpio.h"
#include "../../Interrupt/mcal_interrupt_manager.h"
#include "../../Interrupt/mcal_internal_interrupt.h"
/* Section : Macro Declarations */
#define TIMER3_COUNTER    0x01
#define TIMER3_TIMER    0x00

#define TIMER3_16BIT_OP 0x01
#define TIMER3_8BIT_OP 0x00

#define TIMER3_PRESCALER_OFF   0x00
#define TIMER3_PRESCALER_DIV_2 0x01
#define TIMER3_PRESCALER_DIV_4 0x02
#define TIMER3_PRESCALER_DIV_8 0x03


/* Section : Macro Functions Declarations */
#define TIMER3_ENABLE()     (T3CONbits.TMR3ON = 1)
#define TIMER3_DISABLE()     (T3CONbits.TMR3ON = 0)

#define TIMER3_TIMER_MODE()     (T3CONbits.TMR3CS = 0)
#define TIMER3_COUNTER_MODE()     (T3CONbits.TMR3CS = 1)

#define TIMER3_OSC_ON()             (T3CONbits.T1OSCEN = 1)
#define TIMER3_OSC_OFF()             (T3CONbits.T1OSCEN = 0)

#define TIMER3_ASYNC_CLOCK()             (T3CONbits.T3SYNC = 0)
#define TIMER3_SYNC_CLOCK()             (T3CONbits.T3SYNC = 1)

#define TIMER3_PRESCALER(val)             (T3CONbits.T3CKPS = val)

#define TIMER3_8BIT()                       (T3CONbits.RD16 = 0)
#define TIMER3_16BIT()                       (T3CONbits.RD16 = 1)
/* Section : Data Type Declarations */
    typedef struct{
#if TIMER3_INTERRUPT
    void (* TIMER3_HANDLER)(void);
#if INETRRUPT_PRIORITY
    
    interrupt_priority priority;
#endif
#endif
    uint8 mode :1;
    uint8 size :1;
    uint16 prevalue;
    uint8 prescaler_val;
}timer3_t;


/* Section : Function Declarations */
std_ReturnType TIMER3_INIT(const timer3_t *timer);
std_ReturnType TIMER3_DEINIT(const timer3_t *timer);
std_ReturnType TIMER3_Write_Value(const timer3_t *timer,uint16 val);
std_ReturnType TIMER3_Read_Value(const timer3_t *timer,uint16 *val);
#endif	/* HAL_TIMER3_H */

