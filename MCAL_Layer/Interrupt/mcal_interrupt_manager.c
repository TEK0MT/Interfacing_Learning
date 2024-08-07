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
}
#endif