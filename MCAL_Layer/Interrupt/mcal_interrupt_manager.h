/* 
 * File:   mcal_interrupt_manager.h
 * Author: Mohamed Tarek
 *
 * Created on July 13, 2024, 8:49 AM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H
/*Section : includes */
#include "mcal_interrupt_config.h"
/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */


/* Section : Data Type Declarations */



/* Section : Software Interfacing */
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void RB4_ISR(uint8 n);
void RB5_ISR(uint8 n);
void RB6_ISR(uint8 n);
void RB7_ISR(uint8 n);
void TMR0_ISR(void);
void TMR1_ISR(void);
void TMR2_ISR(void);
void TMR3_ISR(void);
void CCP1_ISR(void);
void CCP2_ISR(void);
void EUSART_TX_ISR(void);
void EUSART_RX_ISR(void);
void MSSP_I2C_ISR(void);
void MSSP_I2C_BC_ISR(void);
#endif	/* MCAL_INTERRUPT_MANAGER_H */

