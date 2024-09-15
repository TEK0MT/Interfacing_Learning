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
#define TIMER0_LOW_PRIORITY()             (INTCON2bits.TMR0IP = 0)
#endif
#endif


#if TIMER1_INTERRUPT == INTERRUPT_ENABLED
#define TIMER1_INTERRUPT_ENABLE()       (PIE1bits.TMR1IE = 1)
#define TIMER1_INTERRUPT_DISABLE()       (PIE1bits.TMR1IE = 0)
#define TIMER1_CLEAR_FLAG()       (PIR1bits.TMR1IF = 0)

#if INETRRUPT_PRIORITY
#define TIMER1_HIGH_PRIORITY()             (IPR1bits.TMR1IP = 1)
#define TIMER1_LOW_PRIORITY()             (IPR1bits.TMR1IP = 0)
#endif
#endif

#if TIMER2_INTERRUPT == INTERRUPT_ENABLED
#define TIMER2_INTERRUPT_ENABLE()       (PIE1bits.TMR2IE = 1)
#define TIMER2_INTERRUPT_DISABLE()       (PIE1bits.TMR2IE = 0)
#define TIMER2_CLEAR_FLAG()       (PIR1bits.TMR2IF = 0)

#if INETRRUPT_PRIORITY
#define TIMER2_HIGH_PRIORITY()             (IPR1bits.TMR2IP = 1)
#define TIMER2_LOW_PRIORITY()             (IPR1bits.TMR2IP = 0)
#endif
#endif

#if TIMER3_INTERRUPT == INTERRUPT_ENABLED
#define TIMER3_INTERRUPT_ENABLE()       (PIE2bits.TMR3IE = 1)
#define TIMER3_INTERRUPT_DISABLE()       (PIE2bits.TMR3IE = 0)
#define TIMER3_CLEAR_FLAG()       (PIR2bits.TMR3IF = 0)

#if INETRRUPT_PRIORITY
#define TIMER3_HIGH_PRIORITY()             (IPR2bits.TMR3IP = 1)
#define TIMER3_LOW_PRIORITY()             (IPR2bits.TMR3IP = 0)
#endif
#endif

#if CCP1_INTERRUPT == INTERRUPT_ENABLED
#define CCP1_INTERRUPT_ENABLE()       (PIE1bits.CCP1IE = 1)
#define CCP1_INTERRUPT_DISABLE()       (PIE1bits.CCP1IE = 0)
#define CCP1_CLEAR_FLAG()       (PIR1bits.CCP1IF = 0)

#if INETRRUPT_PRIORITY
#define CCP1_HIGH_PRIORITY()             (IPR1bits.CCP1IP = 1)
#define CCP1_LOW_PRIORITY()             (IPR1bits.CCP1IP = 0)
#endif
#endif

#if CCP2_INTERRUPT == INTERRUPT_ENABLED
#define CCP2_INTERRUPT_ENABLE()       (PIE2bits.CCP2IE = 1)
#define CCP2_INTERRUPT_DISABLE()       (PIE2bits.CCP2IE = 0)
#define CCP2_CLEAR_FLAG()       (PIR2bits.CCP2IF = 0)

#if INETRRUPT_PRIORITY
#define CCP2_HIGH_PRIORITY()             (IPR2bits.CCP2IP = 1)
#define CCP2_LOW_PRIORITY()             (IPR2bits.CCP2IP = 0)
#endif
#endif

#if USART_TX_INTERRUPT == INTERRUPT_ENABLED
#define TX_INTERRUPT_ENABLE()       (PIE1bits.TXIE = 1)
#define TX_INTERRUPT_DISABLE()       (PIE1bits.TXIE = 0)

#if INETRRUPT_PRIORITY
#define TX_HIGH_PRIORITY()             (IPR1bits.TXIP = 1)
#define TX_LOW_PRIORITY()             (IPR1bits.TXIP = 0)
#endif
#endif

#if USART_RX_INTERRUPT == INTERRUPT_ENABLED
#define RX_INTERRUPT_ENABLE()       (PIE1bits.RCIE = 1)
#define RX_INTERRUPT_DISABLE()       (PIE1bits.RCIE = 0)
#define RX_CLEAR_FLAG()       (PIR1bits.RCIF = 0)
#if INETRRUPT_PRIORITY
#define RX_HIGH_PRIORITY()             (IPR1bits.RCIP = 1)
#define RX_LOW_PRIORITY()             (IPR1bits.RCIP = 0)
#endif
#endif

#if MSSP_INTERRUPT_ENABLED == INTERRUPT_ENABLED
#define MSSP_INTERRUPT_ENABLE()       (PIE1bits.SSPIE = 1)
#define MSSP_INTERRUPT_BUS_COLLISION_ENABLE()       (PIE2bits.BCLIE = 1)
#define MSSP_INTERRUPT_DISABLE()       (PIE1bits.SSPIE = 0)
#define MSSP_INTERRUPT_BUS_COLLISION_DISABLE()       (PIE2bits.BCLIE = 1)
#define MSSP_CLEAR_FLAG()       (PIR1bits.SSPIF = 0)
#define MSSP_INTERRUPT_BUS_COLLISION_CLEAR_FLAG()       (PIR2bits.BCLIF = 0)
#if INETRRUPT_PRIORITY
#define MSSP_HIGH_PRIORITY()             (IPR1bits.SSPIP = 1)
#define MSSP_HIGH_BUS_COLLISION_PRIORITY()             (IPR2bits.BCLIP = 1)
#define MSSP_LOW_PRIORITY()             (IPR1bits.SSPIP = 0)
#define MSSP_LOW_BUS_COLLISION_PRIORITY()             (IPR2bits.BCLIP = 0)
#endif
#endif
/* Section : Data Type Declarations */



/* Section : Function Declarations */


#endif	/* MCAL_INTERNAL_INTERRUPT_H */




