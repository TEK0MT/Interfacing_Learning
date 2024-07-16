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


static void (*RB4_INTERRUPTHANDLERHIGH)(void) = NULL;
static void (*RB4_INTERRUPTHANDLERLOW)(void) = NULL;
static void (*RB5_INTERRUPTHANDLERHIGH)(void) = NULL;
static void (*RB5_INTERRUPTHANDLERLOW)(void) = NULL;
static void (*RB6_INTERRUPTHANDLERHIGH)(void) = NULL;
static void (*RB6_INTERRUPTHANDLERLOW)(void) = NULL;
static void (*RB7_INTERRUPTHANDLERHIGH)(void) = NULL;
static void (*RB7_INTERRUPTHANDLERLOW)(void) = NULL;

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
        ret = Interrupt_INTx_Priority(int_obj);
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

void RB4_ISR(uint8 n){
    /*The INT0 external Interrupt occured (must be cleared)*/
    ONCHANGE_INTERRUPT_CLEAR_FLAG();
    /*Code*/
    
    /*Call back interrupt function*/
    if(!n){
    if(RB4_INTERRUPTHANDLERHIGH){
        RB4_INTERRUPTHANDLERHIGH();
    }
    else{
        /*Nothing*/
    }
    }
    else if(n){
        if(RB4_INTERRUPTHANDLERLOW){
        RB4_INTERRUPTHANDLERLOW();
    }
    else{
        /*Nothing*/
    }
    }
    else{/*Nothing*/}
        ONCHANGE_INTERRUPT_CLEAR_FLAG();
    }

void RB5_ISR(uint8 n){
    /*The INT0 external Interrupt occured (must be cleared)*/
    ONCHANGE_INTERRUPT_CLEAR_FLAG();
    /*Code*/
    
    /*Call back interrupt function*/
    if(!n){
    if(RB5_INTERRUPTHANDLERHIGH){
        RB5_INTERRUPTHANDLERHIGH();
    }
    else{
        /*Nothing*/
    }
    }
    else if(n){
        if(RB5_INTERRUPTHANDLERLOW){
        RB5_INTERRUPTHANDLERLOW();
    }
    else{
        /*Nothing*/
    }
    }
    else{/*Nothing*/}
}
void RB6_ISR(uint8 n){
    /*The INT0 external Interrupt occured (must be cleared)*/
    ONCHANGE_INTERRUPT_CLEAR_FLAG();
    /*Code*/
    
    /*Call back interrupt function*/
    if(!n){
    if(RB6_INTERRUPTHANDLERHIGH){
        RB6_INTERRUPTHANDLERHIGH();
    }
    else{
        /*Nothing*/
    }
    }
    else if(n){
        if(RB6_INTERRUPTHANDLERLOW){
        RB6_INTERRUPTHANDLERLOW();
    }
    else{
        /*Nothing*/
    }
    }
    else{/*Nothing*/}
}

void RB7_ISR(uint8 n){
    /*The INT0 external Interrupt occured (must be cleared)*/
    ONCHANGE_INTERRUPT_CLEAR_FLAG();
    /*Code*/
    
    /*Call back interrupt function*/
   if(!n){
    if(RB7_INTERRUPTHANDLERHIGH){
        RB7_INTERRUPTHANDLERHIGH();
    }
    else{
        /*Nothing*/
    }
    }
    else if(n){
        if(RB7_INTERRUPTHANDLERLOW){
        RB7_INTERRUPTHANDLERLOW();
    }
    else{
        /*Nothing*/
    }
    }
    else{/*Nothing*/}
}

std_ReturnType Interrupt_INTx_DeInit(const interrupt_Intx_t *int_obj){
    std_ReturnType ret = E_OK;
    if(int_obj == NULL){
        ret = E_NOT_OK;
    }
    else{
        Interrupt_INTx_Disable(int_obj);
        
    }
    return ret;
}

std_ReturnType Interrupt_RBx_Init(const interrupt_Rbx_t *int_obj){
    std_ReturnType ret = E_OK;
    if(int_obj == NULL){
        ret = E_NOT_OK;
    }
    else{
        ONCHANGE_INTERRUPT_DISABLE();
        ONCHANGE_INTERRUPT_CLEAR_FLAG();
        #if INETRRUPT_PRIORITY
        INTERRUPT_PRIORITY_ENABLED();
        if(int_obj->priority == LOW_PRIORITY){
        INTERRUPT_LOW_PRIORITY_INTERRUPT_ENABLED();
         ONCHANGE_INTERRUPT_LOW_PRIORITY();   
        }
        else if(int_obj->priority == HIGH_PRIORITY){
            ONCHANGE_INTERRUPT_HIGH_PRIORITY();
        }
        else{/*Nothing*/}
        #else
         INTERRUPT_GLOBAL_INTERRUPT_ENABLED();
         INTERRUPT_PERIPHERAL_ENABLED();
        
        #endif
         ret = gpio_pin_direction_intialize(&(int_obj->pin));
         switch(int_obj->pin.pin){
             case PIN4 : 
                 RB4_INTERRUPTHANDLERHIGH = int_obj->EXT_INTERRUPT_HANDLER_HIGH;
                 RB4_INTERRUPTHANDLERLOW = int_obj->EXT_INTERRUPT_HANDLER_LOW;
                 
                 break;
             case PIN5 :
                 RB5_INTERRUPTHANDLERHIGH = int_obj->EXT_INTERRUPT_HANDLER_HIGH;
                 RB5_INTERRUPTHANDLERLOW = int_obj->EXT_INTERRUPT_HANDLER_LOW;
                 break;
             case PIN6 : 
                 RB6_INTERRUPTHANDLERHIGH = int_obj->EXT_INTERRUPT_HANDLER_HIGH;
                 RB6_INTERRUPTHANDLERLOW = int_obj->EXT_INTERRUPT_HANDLER_LOW;
                 break;
             case PIN7 : 
                 RB7_INTERRUPTHANDLERHIGH = int_obj->EXT_INTERRUPT_HANDLER_HIGH;
                 RB7_INTERRUPTHANDLERLOW = int_obj->EXT_INTERRUPT_HANDLER_LOW;
                 break;
             default :
                 ret = E_NOT_OK;
         }
        ONCHANGE_INTERRUPT_ENABLE();
    }
    return ret;
}
std_ReturnType Interrupt_RBx_DeInit(const interrupt_Rbx_t *int_obj){
    std_ReturnType ret = E_OK;
    if(int_obj == NULL){
        ret = E_NOT_OK;
    }
    else{
        ONCHANGE_INTERRUPT_DISABLE();
    }
    return ret;
}



/**********************************************Helper Function************************************/
static std_ReturnType Interrupt_INTx_Enable(const interrupt_Intx_t *int_obj){
    std_ReturnType ret = E_OK;
    if(int_obj == NULL){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->intx){
            case INTX0:
                #if INETRRUPT_PRIORITY
                 INTERRUPT_HIGH_PRIORITY_INTERRUPT_ENABLED();
                 #else
                INTERRUPT_GLOBAL_INTERRUPT_ENABLED();
                INTERRUPT_GLOBAL_INTERRUPT_ENABLED();
                INTERRUPT_PERIPHERAL_ENABLED();
                #endif
                INTERRUPT_EXTERNAL_INT0_ENBABLE(); 
                break;
            case INTX1:
                #if INETRRUPT_PRIORITY
                INTERRUPT_PRIORITY_ENABLED();
                   if(int_obj->priority == LOW_PRIORITY){
                    INTERRUPT_LOW_PRIORITY_INTERRUPT_ENABLED();
                }
                else if(int_obj->priority == HIGH_PRIORITY){
                    INTERRUPT_HIGH_PRIORITY_INTERRUPT_ENABLED();
                }
                else{/*NOTHING*/}
                #else
                INTERRUPT_GLOBAL_INTERRUPT_ENABLED();
                INTERRUPT_PERIPHERAL_ENABLED();
                #endif
                INTERRUPT_EXTERNAL_INT1_ENBABLE();
                
                break;
            case INTX2:
                #if INETRRUPT_PRIORITY
                INTERRUPT_PRIORITY_ENABLED();
                if(int_obj->priority == LOW_PRIORITY){
                    INTERRUPT_LOW_PRIORITY_INTERRUPT_ENABLED();
                }
                else if(int_obj->priority == HIGH_PRIORITY){
                    INTERRUPT_HIGH_PRIORITY_INTERRUPT_ENABLED();
                }
                else{/*NOTHING*/}
                #else
                INTERRUPT_GLOBAL_INTERRUPT_ENABLED();
                INTERRUPT_PERIPHERAL_ENABLED();
                #endif
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