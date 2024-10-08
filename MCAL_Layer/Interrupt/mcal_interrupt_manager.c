/* 
 * File:   mcal_interrupt_manager.c
 * Author: Mohamed Tarek
 *
 * Created on July 13, 2024, 8:49 AM
 */
#include "mcal_interrupt_manager.h"

static volatile uint8 RB4_F = 1,RB5_F = 1,RB6_F = 1,RB7_F = 1;

#if INETRRUPT_PRIORITY

void __interrupt() InterruptMangaerHigh(){
    
    if((INTCONbits.INT0IE == INTERRUPT_ENABLED) && (INTCONbits.INT0IF == INTERRUPT_OCCURED)){
        INT0_ISR();
    }
    else{
        /*Nothing*/
    }
    if((INTERRUPT_ENABLED == INTCON3bits.INT2IE) && (INTERRUPT_OCCURED == INTCON3bits.INT2IF)){
        INT2_ISR(); /* External Interrupt 2 */
    }
    else{ /* Nothing */ }
    if((INTCONbits.RBIF == INTERRUPT_OCCURED) && (INTCONbits.RBIE == INTERRUPT_ENABLED)){
     RB4_ISR();  
    }
    else{ /* Nothing */ }
}
void __interrupt(low_priority) InterruptMangaerLow(){
    if((INTERRUPT_ENABLED == INTCON3bits.INT1E) && (INTERRUPT_OCCURED == INTCON3bits.INT1F)){
        INT1_ISR(); /* External Interrupt 1 */
    }
    else{ /* Nothing */ }
}
#else

void __interrupt() InterruptMangaer(){
    if((INTCONbits.INT0IE == INTERRUPT_ENABLED) && (INTCONbits.INT0IF == INTERRUPT_OCCURED)){
        INT0_ISR();
    }
    else{
        /*Nothing*/
    }
    if((INTERRUPT_ENABLED == INTCON3bits.INT1E) && (INTERRUPT_OCCURED == INTCON3bits.INT1F)){
        INT1_ISR(); /* External Interrupt 1 */
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLED == INTCON3bits.INT2IE) && (INTERRUPT_OCCURED == INTCON3bits.INT2IF)){
        INT2_ISR(); /* External Interrupt 2 */
    }
    else{ /* Nothing */ }
    if((INTCONbits.RBIE == INTERRUPT_ENABLED) && (INTCONbits.RBIF == 1) && (PORTBbits.RB4 == GPIO_HIGH) && (RB4_F == 1)){
        RB4_F = 0;
        RB4_ISR(0);  
    }
    else{ /* Nothing */ }
    if((INTCONbits.RBIE == INTERRUPT_ENABLED) && (INTCONbits.RBIF == 1) && (PORTBbits.RB4 == GPIO_LOW) && (RB4_F == 0)){
        RB4_F = 1;
        RB4_ISR(1);  
    }
    else{ /* Nothing */ }
    if((INTCONbits.RBIE == INTERRUPT_ENABLED) && (INTCONbits.RBIF == 1) && (PORTBbits.RB5 == GPIO_HIGH) && (RB5_F == 1)){
        RB5_F = 0;
        RB5_ISR(0);  
    }
    else{ /* Nothing */ }
    if((INTCONbits.RBIE == INTERRUPT_ENABLED) && (INTCONbits.RBIF == 1) && (PORTBbits.RB5 == GPIO_LOW) && (RB5_F == 0)){
        RB5_F = 1;
        RB5_ISR(1);  
    }
    else{ /* Nothing */ }
    if((INTCONbits.RBIE == INTERRUPT_ENABLED) && (INTCONbits.RBIF == 1) && (PORTBbits.RB6 == GPIO_HIGH) && (RB6_F == 1)){
        RB6_F = 0;
        RB6_ISR(0);  
    }
    else{ /* Nothing */ }
    if((INTCONbits.RBIE == INTERRUPT_ENABLED) && (INTCONbits.RBIF == 1) && (PORTBbits.RB6 == GPIO_LOW) && (RB6_F == 0)){
        RB6_F = 1;
        RB4_ISR(1);  
    }
    else{ /* Nothing */ }
    if((INTCONbits.RBIE == INTERRUPT_ENABLED) && (INTCONbits.RBIF == 1) && (PORTBbits.RB7 == GPIO_HIGH) && (RB7_F == 1)){
        RB7_F = 0;
        RB7_ISR(0);  
    }
    else{ /* Nothing */ }if((INTCONbits.RBIE == INTERRUPT_ENABLED) && (INTCONbits.RBIF == 1) && (PORTBbits.RB7 == GPIO_HIGH) && (RB7_F == 0)){
        RB7_F = 0;
        RB7_ISR(1);  
    }
    else{ /* Nothing */ }
    if((INTCONbits.TMR0IE == 1) && (INTCONbits.TMR0IF == 1)){
        TMR0_ISR();
    }
    else{/* Nothing */}
    if((PIE1bits.TMR1IE == 1) && (PIR1bits.TMR1IF == 1)){
        TMR1_ISR();
    }
    else{/* Nothing */}
    
    if((T2CONbits.TMR2ON == 1) && (PIR1bits.TMR2IF == 1)){
        TMR2_ISR();
    }
    else{/* Nothing */}
    if((T3CONbits.TMR3ON == 1) && (PIR2bits.TMR3IF == 1)){
        TMR3_ISR();
    }
    else{/* Nothing */}
    
    if((PIE1bits.CCP1IE == 1) && (PIR1bits.CCP1IF == 1)){
        CCP1_ISR();
    }
    else{/* Nothing */}
    
    if((PIE2bits.CCP2IE == 1) && (PIR2bits.CCP2IF == 1)){
        CCP2_ISR();
    }
    else{/* Nothing */}
    
     if((INTERRUPT_ENABLED == PIE1bits.TXIE) && (INTERRUPT_OCCURED == PIR1bits.TXIF)){
        EUSART_TX_ISR();
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLED == PIE1bits.RCIE) && (INTERRUPT_OCCURED == PIR1bits.RCIF)){
        EUSART_RX_ISR();
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLED == PIE1bits.SSPIE) && (INTERRUPT_OCCURED == PIR1bits.SSPIF)){
        MSSP_I2C_ISR();
    }
    else{ /* Nothing */ }
}
#endif