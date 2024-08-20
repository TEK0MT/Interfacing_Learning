/* 
 * File:   hal_timer2.c
 * Author: Mohamed Tarek
 *
 * Created on August 20, 2024, 6:36 AM
 */
#include "hal_timer2.h"

static void (*TMR2_HANDLER)(void);

static uint8 preval = ZERO_INIT;

std_ReturnType TIMER2_INIT(const timer2_t *timer){
    std_ReturnType ret = E_OK;
    if(timer == NULL){
        ret = E_NOT_OK;
    }
    else{
        TIMER2_DISABLE();
        TIMER2_PRESCALER(timer->prescaler_val);
        TIMER2_POSTSCALE(timer->postscale_val);
        TMR2 = timer->prevalue;
        TMR2_HANDLER = timer->TIMER2_HANDLER;
        preval = timer->prevalue;
        #if INETRRUPT_PRIORITY
    INTERRUPT_PRIORITY_ENABLED();
    TIMER2_CLEAR_FLAG();
    
    if(timer->priority == HIGH_PRIORITY){
        INTERRUPT_HIGH_PRIORITY_INTERRUPT_ENABLED();
        TIMER2_HIGH_PRIORITY();
    }
    else if(timer->priority == LOW_PRIORITY){
        INTERRUPT_LOW_PRIORITY_INTERRUPT_ENABLED();
        TIMER2_LOW_PRIORITY();
    }
#elif TIMER1_INTERRUPT
    INTERRUPT_GLOBAL_INTERRUPT_ENABLED();
    INTERRUPT_PERIPHERAL_ENABLED();
    TIMER2_INTERRUPT_ENABLE();
    TIMER2_CLEAR_FLAG();
#endif
    TIMER2_ENABLE();
    }
    return ret;
}
std_ReturnType TIMER2_DEINIT(const timer2_t *timer){
    std_ReturnType ret = E_OK;
    if(timer == NULL){
        ret = E_NOT_OK;
    }
    else{
         TIMER2_DISABLE();
        
        #if TIMER2_INTERRUPT
    TIMER2_INTERRUPT_DISABLE();
    #endif
    }
    return ret;
}
std_ReturnType TIMER2_Write_Value(const timer2_t *timer,uint8 val){
    std_ReturnType ret = E_OK;
    if(timer == NULL){
        ret = E_NOT_OK;
    }
    else{
        TMR2 = timer->prevalue;
    }
    return ret;
}
std_ReturnType TIMER2_Read_Value(const timer2_t *timer,uint8 *val){
    std_ReturnType ret = E_OK;
    if(timer == NULL){
        ret = E_NOT_OK;
    }
    else{
        *val = TMR2;
    }
    return ret;
}

void TMR2_ISR(void){
    TIMER2_CLEAR_FLAG();
    TMR2 = preval;
    if(TMR2_HANDLER){
        TMR2_HANDLER();
    }
}