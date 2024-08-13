/* 
 * File:   hal_timer0.c
 * Author: Mohamed Tarek
 *
 * Created on August 13, 2024, 3:36 AM
 */
#include "hal_timer0.h"

#if TIMER0_INTERRUPT == INTERRUPT_ENABLED
static void(*ISR_TIMER0)(void);
#endif
static std_ReturnType TIMER0_Size_SELECT(const timer0_t *timer);
static std_ReturnType TIMER0_MODE_SELECT(const timer0_t *timer);
static std_ReturnType TIMER0_PRESCALER_CFG(const timer0_t *timer);

static uint16 preload = ZERO_INIT;

std_ReturnType TIMER0_INIT(const timer0_t *timer){
    std_ReturnType ret = E_OK;
    if(timer == NULL){
        ret = E_NOT_OK;
    }
    else{
        TIMER0_DISABLE();
        TIMER0_Size_SELECT(timer);
        TIMER0_MODE_SELECT(timer);
        TIMER0_PRESCALER_CFG(timer);
        TMR0H = ((timer->prevalue) >> 8);
        TMR0L = (uint8)(timer->prevalue);
        preload = timer->prevalue;
        #if TIMER0_INTERRUPT == INTERRUPT_ENABLED
        TIMER0_INTERRUPT_ENABLE();
        TIMER0_CLEAR_FLAG();
        ISR_TIMER0 = timer->TIMER0_HANDLER;
        #if INETRRUPT_PRIORITY
        INTERRUPT_PRIORITY_ENABLED();
        if(timer->priority == HIGH_PRIORITY){
            INTERRUPT_HIGH_PRIORITY_INTERRUPT_ENABLED();
            TIMER0_HIGH_PRIORITY() 
        }
        else if(timer->priority == LOW_PRIORITY){
            INTERRUPT_LOW_PRIORITY_INTERRUPT_ENABLED()();
            TIMER1_LOW_PRIORITY() 
        }
    #else
    INTERRUPT_GLOBAL_INTERRUPT_ENABLED();
    INTERRUPT_PERIPHERAL_ENABLED();
    #endif
    #endif
    TIMER0_ENABLE();
    }
    return ret;
}
std_ReturnType TIMER0_DEINIT(const timer0_t *timer){
    std_ReturnType ret = E_OK;
    if(timer == NULL){
        ret = E_NOT_OK;
    }
    else{
        TIMER0_DISABLE();
        #if TIMER0_INTERRUPT == INTERRUPT_ENABLED
        TIMER0_INTERRUPT_DISABLE();
        #endif
    }
    return ret;
}
std_ReturnType TIMER0_Write_Value(const timer0_t *timer,uint16 var){
    std_ReturnType ret = E_OK;
    if(timer == NULL){
        ret = E_NOT_OK;
    }
    else{
        TMR0H = (var >> 8);
        TMR0L = (uint8)(var);
    }
    return ret;
}
std_ReturnType TIMER0_Read_Value(const timer0_t *timer,uint16 *var){
    std_ReturnType ret = E_OK;
    uint8 low_reg = ZERO_INIT;
    uint8 high_reg = ZERO_INIT;
    if(timer == NULL){
        ret = E_NOT_OK;
    }
    else{
        low_reg = TMR0L;
        high_reg = TMR0H;
        *var = (uint16)((high_reg << 8) + low_reg);
    }
    return ret;
}


static std_ReturnType TIMER0_Size_SELECT(const timer0_t *timer){
    std_ReturnType ret = E_OK;
    if(timer == NULL){
        ret = E_NOT_OK;
    }
    else{
        if(timer->size == TIMER_16BIT){
            TIMER0_16BIT_MODE();
        }
        else if(timer->size == TIMER_8BIT){
            TIMER0_8BIT_MODE();
        }
        else{ret = E_NOT_OK;}
    }
    return ret;
}

static std_ReturnType TIMER0_MODE_SELECT(const timer0_t *timer){
    std_ReturnType ret = E_OK;
    if(timer == NULL){
        ret = E_NOT_OK;
    }
    else{
        if(timer->mode == TIMER0_TIMER_MODE){
            INTERNAL_CLOCK();
        }
        else if(timer->mode == TIMER0_COUNTER_MODE){
            EXTERNAL_PIN_CLOCK();
            if(timer->edge == TIMER0_RISING_EDGE_SELECT){
                TIMER0_RISING_EDGE();
            }
            else if(timer->edge == TIMER0_FALLING_EDGE_SELECT){
                TIMER0_FALLING_EDGE();
            }
            else{ret = E_NOT_OK;}
        }
        else{ret = E_NOT_OK;}
    }
    return ret;
}
static std_ReturnType TIMER0_PRESCALER_CFG(const timer0_t *timer){
    std_ReturnType ret = E_OK;
    if(timer == NULL){
        ret = E_NOT_OK;
    }
    else{
        if(timer->prescaler == TRM_PRESCALER_OFF){
            TIMER0_PRESCALER_OFF();
        }
        else if(timer->prescaler == TRM_PRESCALER_ON){
            
            TIMER0_PRESCALER_ON();
            T0CONbits.T0PS = timer->prescaler_val;
        }
        else{ret = E_NOT_OK;}
    }
    return ret;
}
#if TIMER0_INTERRUPT == INTERRUPT_ENABLED
void TMR0_ISR(void){
    TIMER0_CLEAR_FLAG();
    TMR0H = (preload >> 8);
    TMR0L = (uint8)(preload);
    if(ISR_TIMER0){
        ISR_TIMER0();
    }
    else{
        /*NOTHING*/
    }
}
#endif