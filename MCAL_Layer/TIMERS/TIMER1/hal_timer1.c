/* 
 * File:   hal_timer1.c
 * Author: Mohamed Tarek
 *
 * Created on August 19, 2024, 3:15 AM
 */
#include "hal_timer1.h"



static uint16 preval;

static void (*TMR1_HANDLER)(void);

static std_ReturnType TIMER1_MODE_SELECT(const timer1_t *timer);
static std_ReturnType TIMER1_SIZE_SELECT(const timer1_t *timer);



std_ReturnType TIMER1_INIT(const timer1_t *timer){
    std_ReturnType ret = E_OK;
    if(timer == NULL){
        ret = E_NOT_OK;
    }
    else{
        TIMER1_DISABLE();
        TIMER1_MODE_SELECT(timer);
        TIMER1_SIZE_SELECT(timer);
        TIMER1_PRESCALER(timer->prescaler_val);
        TMR1H = (uint8)((timer->prevalue) >> 8) ;
        TMR1L = (uint8)(timer->prevalue);
        preval = timer->prevalue;
        TMR1_HANDLER = timer->TIMER1_HANDLER;
#if INETRRUPT_PRIORITY
    INTERRUPT_PRIORITY_ENABLED();
    TIMER1_CLEAR_FLAG();
    
    if(timer->priority == HIGH_PRIORITY){
        INTERRUPT_HIGH_PRIORITY_INTERRUPT_ENABLED();
        TIMER1_HIGH_PRIORITY();
    }
    else if(timer->priority == LOW_PRIORITY){
        INTERRUPT_LOW_PRIORITY_INTERRUPT_ENABLED();
        TIMER1_LOW_PRIORITY();
    }
#elif TIMER1_INTERRUPT
    INTERRUPT_GLOBAL_INTERRUPT_ENABLED();
    INTERRUPT_PERIPHERAL_ENABLED();
    TIMER1_INTERRUPT_ENABLE();
    TIMER1_CLEAR_FLAG();
#endif
    TIMER1_ENABLE();
    }
    return ret;
}
std_ReturnType TIMER1_DEINIT(const timer1_t *timer){
    
    std_ReturnType ret = E_OK;
    if(timer == NULL){
        ret = E_NOT_OK;
    }
    else{
        TIMER1_DISABLE();
        
        #if TIMER1_INTERRUPT
    TIMER1_INTERRUPT_DISABLE();
    #endif
    TIMER1_ENABLE();
    }
    return ret;
}
std_ReturnType TIMER1_Write_Value(const timer1_t *timer,uint16 val){
    uint16 l_val = val;
    std_ReturnType ret = E_OK;
    if(timer == NULL){
        ret = E_NOT_OK;
    }
    else{
        TMR1H = (uint8)((l_val >> 8));
        TMR1L = (uint8)(l_val );
    }
    return ret;
}
std_ReturnType TIMER1_Read_Value(const timer1_t *timer,uint16 *val){
    uint8 l_val = ZERO_INIT;
    uint8 h_val = ZERO_INIT;
    std_ReturnType ret = E_OK;
    if(timer == NULL){
        ret = E_NOT_OK;
    }
    else{
        l_val = TMR1L;
        h_val = TMR1H;
        *val = (uint16)(l_val + (h_val << 8));
    }
    return ret;
}

static std_ReturnType TIMER1_MODE_SELECT(const timer1_t *timer){
    std_ReturnType ret = E_OK;
    if(timer == NULL){
        ret = E_NOT_OK;
    }
    else{
        switch(timer->mode){
            case TIMER1_TIMER :
                TIMER1_TIMER_MODE();
                break;
            case TIMER1_COUNTER :
                TIMER1_COUNTER_MODE();
                break;
            default :
                ret = E_NOT_OK;
        }
        
    }
    return ret;
}

static std_ReturnType TIMER1_SIZE_SELECT(const timer1_t *timer){
    std_ReturnType ret = E_OK;
    if(timer == NULL){
        ret = E_NOT_OK;
    }
    else{
        switch(timer->size){
            case TIMER1_8BIT_OP :
                TIMER1_8BIT();
                break;
            case TIMER1_16BIT_OP :
                TIMER1_16BIT();
                break;
            default :
                ret = E_NOT_OK;
        }
        
    }
    return ret;
}

void TMR1_ISR(void){
    TIMER1_CLEAR_FLAG();
    TMR1H = (uint8)(preval >> 8);
    TMR1L = (uint8)preval;
    if(TMR1_HANDLER){
        TMR1_HANDLER();
    }
    else{}
}