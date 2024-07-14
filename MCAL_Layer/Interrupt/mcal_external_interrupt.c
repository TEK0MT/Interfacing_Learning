/* 
 * File:   mcal_external_interrupt.c
 * Author: Mohamed Tarek
 *
 * Created on July 13, 2024, 8:50 AM
 */
#include "mcal_external_interrupt.h"

static void (*INT0_INTERRUPTHANDLER)(void) = NULL;
static void (*INT1_INTERRUPTHANDLER)(void) = NULL;
static void (*INT2_INTERRUPTHANDLER)(void) = NULL;

static std_ReturnType INT0_INTERRUPT_HANDLER(void(*Interrupt_Handler)(void));
static std_ReturnType INT1_INTERRUPT_HANDLER(void(*Interrupt_Handler)(void));
static std_ReturnType INT2_INTERRUPT_HANDLER(void(*Interrupt_Handler)(void));

static std_ReturnType Interrupt_INTx_Enable(const interrupt_Intx_t *int_obj);
static std_ReturnType Interrupt_INTx_Disable(const interrupt_Intx_t *int_obj);
static std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_Intx_t *int_obj);
static std_ReturnType Interrupt_INTx_Edge_Src(const interrupt_Intx_t *int_obj);
static std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_Intx_t *int_obj);
static std_ReturnType Interrupt_INTx_Priority(const interrupt_Intx_t *int_obj);
static std_ReturnType Set_Interrupt_Handler(const interrupt_Intx_t *int_obj);


std_ReturnType Interrupt_INTx_Init(const interrupt_Intx_t *int_obj){
    std_ReturnType ret = E_OK;
    if(int_obj == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = Interrupt_INTx_Disable(int_obj);
        ret = Interrupt_INTx_Clear_Flag(int_obj);
        ret = Interrupt_INTx_Edge_Src(int_obj);
        ret = Interrupt_INTx_Pin_Init(int_obj);
        ret = Set_Interrupt_Handler(int_obj);
        ret = Interrupt_INTx_Enable(int_obj);
    }
    return ret;
}

void INT0_ISR(void){
    /*The INT0 external Interrupt occured (must be cleared)*/
    INTERRUPT_EXTERNAL_INT0_CLEAR_FLAG();
    /*Code*/
    
    /*Call back interrupt function*/
    if(INT0_INTERRUPTHANDLER){
        INT0_INTERRUPTHANDLER();
    }
    else{
        /*Nothing*/
    }
}

void INT1_ISR(void){
    /*The INT0 external Interrupt occured (must be cleared)*/
    INTERRUPT_EXTERNAL_INT1_CLEAR_FLAG();
    /*Code*/
    
    /*Call back interrupt function*/
    if(INT1_INTERRUPTHANDLER){
        INT1_INTERRUPTHANDLER();
    }
    else{
        /*Nothing*/
    }
}

void INT2_ISR(void){
    /*The INT0 external Interrupt occured (must be cleared)*/
    INTERRUPT_EXTERNAL_INT2_CLEAR_FLAG();
    /*Code*/
    
    /*Call back interrupt function*/
    if(INT2_INTERRUPTHANDLER){
        INT2_INTERRUPTHANDLER();
    }
    else{
        /*Nothing*/
    }
}




std_ReturnType Interrupt_INTx_DeInit(const interrupt_Intx_t *int_obj){
    std_ReturnType ret = E_OK;
    if(int_obj == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = Interrupt_INTx_Disable(int_obj);
    }
    return ret;
}

std_ReturnType Interrupt_RBx_Init(const interrupt_Intx_t *int_obj);
std_ReturnType Interrupt_RBx_DeInit(const interrupt_Rbx_t *int_obj);



/**********************************************Helper Function************************************/
static std_ReturnType Interrupt_INTx_Enable(const interrupt_Intx_t *int_obj){
    std_ReturnType ret = E_OK;
    if(int_obj == NULL){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->intx){
            case INTX0:
                INTERRUPT_GLOBAL_INTERRUPT_ENABLED();
                INTERRUPT_PERIPHERAL_ENABLED();
                INTERRUPT_EXTERNAL_INT0_ENBABLE(); 
                break;
            case INTX1:
                INTERRUPT_GLOBAL_INTERRUPT_ENABLED();
                INTERRUPT_PERIPHERAL_ENABLED();
                INTERRUPT_EXTERNAL_INT1_ENBABLE();
                break;
            case INTX2:
                INTERRUPT_GLOBAL_INTERRUPT_ENABLED();
                INTERRUPT_PERIPHERAL_ENABLED();
                INTERRUPT_EXTERNAL_INT2_ENBABLE(); 
                break;
            default :
                ret = E_NOT_OK;
        }
    }
    return ret;
}

static std_ReturnType Interrupt_INTx_Disable(const interrupt_Intx_t *int_obj){
    std_ReturnType ret = E_OK;
    if(int_obj == NULL){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->intx){
            case INTX0: INTERRUPT_EXTERNAL_INT0_DISABLE(); break;
            case INTX1: INTERRUPT_EXTERNAL_INT1_DISABLE(); break;
            case INTX2: INTERRUPT_EXTERNAL_INT2_DISABLE(); break;
            default :
                ret = E_NOT_OK;
        }
    }
    return ret;
}
static std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_Intx_t *int_obj){
    std_ReturnType ret = E_OK;
    if(int_obj == NULL){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->intx){
            case INTX0: INTERRUPT_EXTERNAL_INT0_CLEAR_FLAG(); break;
            case INTX1: INTERRUPT_EXTERNAL_INT1_CLEAR_FLAG(); break;
            case INTX2: INTERRUPT_EXTERNAL_INT2_CLEAR_FLAG(); break;
            default :
                ret = E_NOT_OK;
        }
    }
    return ret;
}

static std_ReturnType Interrupt_INTx_Edge_Src(const interrupt_Intx_t *int_obj){
    std_ReturnType ret = E_OK;
    if(int_obj == NULL){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->intx){
            case INTX0:
                if(int_obj->edge == Falling_Edge){
                    INTERRUPT_EXTERNAL_INT0_FALLING_EDGE();
                }
                else{
                    INTERRUPT_EXTERNAL_INT0_RISING_EDGE();
                }
                break;
            case INTX1:
                if(int_obj->edge == Falling_Edge){
                    INTERRUPT_EXTERNAL_INT1_FALLING_EDGE();
                }
                else{
                    INTERRUPT_EXTERNAL_INT1_RISING_EDGE();
                }
                break;
            case INTX2:
                if(int_obj->edge == Falling_Edge){
                    INTERRUPT_EXTERNAL_INT2_FALLING_EDGE();
                }
                else{
                    INTERRUPT_EXTERNAL_INT2_RISING_EDGE();
                }
                break;
            default :
                ret = E_NOT_OK;
        }
    }
    return ret;
}
static std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_Intx_t *int_obj){
    std_ReturnType ret = E_OK;
    if(int_obj == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_direction_intialize(&(int_obj->pin));
    }
    return ret;
}
static std_ReturnType INT0_INTERRUPT_HANDLER(void(*Interrupt_Handler)(void)){
    std_ReturnType ret = E_OK;
    if(Interrupt_Handler == NULL){
        ret = E_NOT_OK;
    }
    else{
        INT0_INTERRUPTHANDLER = Interrupt_Handler;
    }
    return ret;
}
static std_ReturnType INT1_INTERRUPT_HANDLER(void(*Interrupt_Handler)(void)){
    std_ReturnType ret = E_OK;
    if(Interrupt_Handler == NULL){
        ret = E_NOT_OK;
    }
    else{
        INT1_INTERRUPTHANDLER = Interrupt_Handler;
    }
    return ret;
}
static std_ReturnType INT2_INTERRUPT_HANDLER(void(*Interrupt_Handler)(void)){
    std_ReturnType ret = E_OK;
    if(Interrupt_Handler == NULL){
        ret = E_NOT_OK;
    }
    else{
        INT2_INTERRUPTHANDLER = Interrupt_Handler;
    }
    return ret;
}
static std_ReturnType Set_Interrupt_Handler(const interrupt_Intx_t *int_obj){
    std_ReturnType ret = E_OK;
    if(int_obj == NULL){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->intx){
            case INTX0: INT0_INTERRUPT_HANDLER(int_obj->EXT_INTERRUPT_HANDLER); break;
            case INTX1: INT1_INTERRUPT_HANDLER(int_obj->EXT_INTERRUPT_HANDLER); break;
            case INTX2: INT2_INTERRUPT_HANDLER(int_obj->EXT_INTERRUPT_HANDLER); break;
            default :
                ret = E_NOT_OK;
        }
    }
    return ret;
}
#if INETRRUPT_PRIORITY
static std_ReturnType Interrupt_INTx_Priority(const interrupt_Intx_t *int_obj){
    std_ReturnType ret = E_OK;
    if(int_obj == NULL){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->intx){
            case INTX0:
                
                break;
            case INTX1:
                if(int_obj->priority == LOW_PRIORITY){
                    INTERRUPT_EXTERNAL_INT1_LOW_PRIORITY();
                }
                else{
                    INTERRUPT_EXTERNAL_INT1_HIGH_PRIORITY();
                }
                break;
            case INTX2:
                if(int_obj->priority == LOW_PRIORITY){
                    INTERRUPT_EXTERNAL_INT2_LOW_PRIORITY();
                }
                else{
                    INTERRUPT_EXTERNAL_INT2_HIGH_PRIORITY();
                }
                break;
            default :
                ret = E_NOT_OK;
        }
    }
    return ret;
}

#endif