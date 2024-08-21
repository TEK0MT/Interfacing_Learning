/* 
 * File:   hal_timer3.c
 * Author: Mohamed Tarek
 *
 * Created on August 21, 2024, 7:35 AM
 */
#include "hal_timer3.h"



static uint16 preval;

static void (*TMR3_HANDLER)(void);

static std_ReturnType TIMER3_MODE_SELECT(const timer3_t *timer);
static std_ReturnType TIMER3_SIZE_SELECT(const timer3_t *timer);



std_ReturnType TIMER3_INIT(const timer3_t *timer){
    std_ReturnType ret = E_OK;
    if(timer == NULL){
        ret = E_NOT_OK;
    }
    else{
        TIMER3_DISABLE();
        TIMER3_MODE_SELECT(timer);
        TIMER3_SIZE_SELECT(timer);
        TIMER3_PRESCALER(timer->prescaler_val);
        TMR3H = (uint8)((timer->prevalue) >> 8) ;
        TMR3L = (uint8)(timer->prevalue);
        preval = timer->prevalue;
        TIMER3_ASYNC_CLOCK();
        TMR3_HANDLER = timer->TIMER3_HANDLER;
#if INETRRUPT_PRIORITY
    INTERRUPT_PRIORITY_ENABLED();
    TIMER3_CLEAR_FLAG();
    
    if(timer->priority == HIGH_PRIORITY){
        INTERRUPT_HIGH_PRIORITY_INTERRUPT_ENABLED();
        TIMER3_HIGH_PRIORITY();
    }
    else if(timer->priority == LOW_PRIORITY){
        INTERRUPT_LOW_PRIORITY_INTERRUPT_ENABLED();
        TIMER3_LOW_PRIORITY();
    }
#elif TIMER1_INTERRUPT
    INTERRUPT_GLOBAL_INTERRUPT_ENABLED();
    INTERRUPT_PERIPHERAL_ENABLED();
    TIMER3_INTERRUPT_ENABLE();
    TIMER3_CLEAR_FLAG();
#endif
    TIMER3_ENABLE();
    }
    return ret;
}
std_ReturnType TIMER3_DEINIT(const timer3_t *timer){
    
    std_ReturnType ret = E_OK;
    if(timer == NULL){
        ret = E_NOT_OK;
    }
    else{
        TIMER3_DISABLE();
        
        #if TIMER3_INTERRUPT
    TIMER3_INTERRUPT_DISABLE();
    #endif
    
    }
    return ret;
}
std_ReturnType TIMER3_Write_Value(const timer3_t *timer,uint16 val){
    uint16 l_val = val;
    std_ReturnType ret = E_OK;
    if(timer == NULL){
        ret = E_NOT_OK;
    }
    else{
        TMR3H = (uint8)((l_val >> 8));
        TMR3L = (uint8)(l_val );
    }
    return ret;
}
std_ReturnType TIMER3_Read_Value(const timer3_t *timer,uint16 *val){
    uint8 l_val = ZERO_INIT;
    uint8 h_val = ZERO_INIT;
    std_ReturnType ret = E_OK;
    if(timer == NULL){
        ret = E_NOT_OK;
    }
    else{
        l_val = TMR3L;
        h_val = TMR3H;
        *val = (uint16)(l_val + (h_val << 8));
    }
    return ret;
}

static std_ReturnType TIMER3_MODE_SELECT(const timer3_t *timer){
    std_ReturnType ret = E_OK;
    if(timer == NULL){
        ret = E_NOT_OK;
    }
    else{
        switch(timer->mode){
            case TIMER3_TIMER :
                TIMER3_TIMER_MODE();
                break;
            case TIMER3_COUNTER :
                TIMER3_COUNTER_MODE();
                break;
            default :
                ret = E_NOT_OK;
        }
        
    }
    return ret;
}

static std_ReturnType TIMER3_SIZE_SELECT(const timer3_t *timer){
    std_ReturnType ret = E_OK;
    if(timer == NULL){
        ret = E_NOT_OK;
    }
    else{
        switch(timer->size){
            case TIMER3_8BIT_OP :
                TIMER3_8BIT();
                break;
            case TIMER3_16BIT_OP :
                TIMER3_16BIT();
                break;
            default :
                ret = E_NOT_OK;
        }
        
    }
    return ret;
}

void TMR3_ISR(void){
    TIMER3_CLEAR_FLAG();
    TMR3H = (uint8)(preval >> 8);
    TMR3L = (uint8)preval;
    if(TMR3_HANDLER){
        TMR3_HANDLER();
    }
    else{}
}
