/* 
 * File:   mcal_internal_interrupt.h
 * Author: Mohamed Tarek
 *
 * Created on July 13, 2024, 8:50 AM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H
/*Section : includes */
#include "mcal_interrupt_config.h"
/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */
#if ADC_INTERRUPT == INTERRUPT_ENABLED
#define ADC_INTERRUPT_ENABLE()         (PIE1bits.ADIE = 1)
#define ADC_INTERRUPT_DISABLE()         (PIE1bits.ADIE = 0)

#define ADC_CLEAN_FLAG()                (PIR1bits.ADIF = 0)

#if INETRRUPT_PRIORITY
#define ADC_HIGH_PRIORITY()             (IPRbits.ADIP = 1)
#define ADC_LOW_PRIORITY()             (IPRbits.ADIP = 0)
#endif
#endif

#if TIMER0_INTERRUPT == INTERRUPT_ENABLED
#define TIMER0_INTERRUPT_ENABLE()       (INTCONbits.TMR0IE = 1)
#define TIMER0_INTERRUPT_DISABLE()       (INTCONbits.TMR0IE = 0)
#define TIMER0_CLEAR_FLAG()       (INTCONbits.TMR0IF = 0)

#if INETRRUPT_PRIORITY
#define TIMER0_HIGH_PRIORITY()             (INTCON2bits.TMR0IP = 1)
#define TIMER1_LOW_PRIORITY()             (INTCON2bits.TMR0IP = 0)
#endif
#endif
/* Section : Data Type Declarations */



/* Section : Function Declarations */


#endif	/* MCAL_INTERNAL_INTERRUPT_H */




