/* 
 * File:   mcal_interrupt_manager.c
 * Author: Mohamed Tarek
 *
 * Created on July 13, 2024, 8:49 AM
 */
#include "mcal_interrupt_manager.h"

#if INETRRUPT_PRIORITY

void __interrupt() InterruptMangaerHigh(){
    
}
void __interrupt(low_priority) InterruptMangaerLow(){
    
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
}
#endif