/* 
 * File:   hal_cpp.c
 * Author: Mohamed Tarek
 *
 * Created on August 24, 2024, 3:54 AM
 */
#include "hal_cpp.h"

static void (*Interrupt_Handler_CCP1)(void);
static void (*Interrupt_Handler_CCP2)(void);


static std_ReturnType CCP_Interrupt_Config(const ccp_t* ccp);
static std_ReturnType CCP_Capture_Config(const ccp_t* ccp);
static std_ReturnType CCP_Compare_Config(const ccp_t* ccp);
static std_ReturnType CCP_PWM_Config(const ccp_t* ccp);

std_ReturnType CCP_Init(const ccp_t* ccp){
    std_ReturnType ret = E_OK;
    if(ccp == NULL){
        ret = E_NOT_OK;
    }
    else{
        if(ccp->ccpx == CCP1_INST){
        CCP1_MODE_SELECT(CCP_PWM_COMPARE_CAPTURE_DISABLE);
        }
        else if(ccp->ccpx == CCP2_INST){
        CCP2_MODE_SELECT(CCP_PWM_COMPARE_CAPTURE_DISABLE);
        }
        else{ /* Nothing */}
        
        
        
        if(ccp->mode == CCP_CAPTURE_MODE){
            ret = CCP_Capture_Config(ccp);
        }
        else if(ccp->mode == CCP_COMPARE_MODE){
            ret = CCP_Compare_Config(ccp);
        }
        else if(ccp->mode == CCP_PWM_MODE){
            ret = CCP_PWM_Config(ccp);
        }
        else{ /* Nothing */}
        ret = gpio_pin_initialize(&(ccp->pin));
        
        CCP_Interrupt_Config(ccp);
    }
    return ret;
}
std_ReturnType CCP_DeInit(const ccp_t* ccp){
    std_ReturnType ret = E_OK;
    if(ccp == NULL){
        ret = E_NOT_OK;
    }
    else{
         if(ccp->ccpx == CCP1_INST){
        CCP1_MODE_SELECT(CCP_PWM_COMPARE_CAPTURE_DISABLE);
#if CCP1_INTERRUPT == INTERRUPT_ENABLED
        CCP1_INTERRUPT_DISABLE();
#endif
        }
        else if(ccp->ccpx == CCP2_INST){
        CCP2_MODE_SELECT(CCP_PWM_COMPARE_CAPTURE_DISABLE);
        #if CCP2_INTERRUPT == INTERRUPT_ENABLED
        CCP2_INTERRUPT_DISABLE();
#endif
        }
        else{ /* Nothing */}

    }
    return ret;
}
#if CCP1_GEN_MODE_SELECT == CCP_CAPTURE_GEN_MODE
std_ReturnType CCP_IsCaptureReady(uint8 *status){
    std_ReturnType ret = E_OK;
    if(status == NULL){
        ret = E_NOT_OK;
    }
    else{
        if(PIR1bits.CCP1IF == CCP_CAPTURE_READY){
            *status = CCP_CAPTURE_READY;
            CCP1_CLEAR_FLAG();
        }
        else {
            *status = CCP_CAPTURE_NOT_READY;
        }
    }
    return ret;
}
std_ReturnType CCP_Capture_Mode_Read_Value(uint16 *value){
    std_ReturnType ret = E_OK;
    CCP_REG_T obj = {.ccp_lval = 0,.ccp_hval = 0};
    if(value == NULL){
        ret = E_NOT_OK;
    }
    else{
        obj.ccp_lval = CCPR1L;
        obj.ccp_hval = CCPR1H;
        *value = obj.value;
    }
    return ret;
}
#endif
#if CCP1_GEN_MODE_SELECT == CCP_COMPARE_GEN_MODE
std_ReturnType CCP_IsCompareReady(uint8 *status){
    std_ReturnType ret = E_OK;
    if(status == NULL){
        ret = E_NOT_OK;
    }
    else{
        if(PIR1bits.CCP1IF == CCP_CAPTURE_READY){
            *status = CCP_CAPTURE_READY;
            CCP1_CLEAR_FLAG();
        }
        else {
            *status = CCP_CAPTURE_NOT_READY;
        }
    }
    return ret;
}
std_ReturnType CCP_Compare_Set_Value(const ccp_t* ccp,uint16 value){
    std_ReturnType ret = E_OK;
     CCP_REG_T obj = {.ccp_lval = 0,.ccp_hval = 0};
    if(ccp == NULL){
        ret = E_NOT_OK;
    }
    else{
        obj.value = value;
        if(ccp->ccpx == CCP1_INST){
        CCPR1L = obj.ccp_lval;
        CCPR1H = obj.ccp_hval;
        }
        else if(ccp->ccpx == CCP2_INST){
            CCPR2L = obj.ccp_lval;
        CCPR2H = obj.ccp_hval;
        }
        else{/* Nothing */}
    }
    return ret;
}
#endif
#if (CCP1_GEN_MODE_SELECT == CCP_PWM_GEN_MODE) || (CCP2_GEN_MODE_SELECT == CCP_PWM_GEN_MODE)
std_ReturnType CCP_PWM_Set_Duty(const ccp_t* ccp,uint8 val){
    std_ReturnType ret = E_OK;
    if(ccp == NULL){
        ret = E_NOT_OK;
    }
    else{
        uint16 pwm_period = (uint16)((float)4 *((float)PR2 + 1.0) * ((float)val / 100.0));
        if(ccp->ccpx == CCP1_INST){
        CCP1CONbits.DC1B = (uint8)(pwm_period & 0x0003);
        CCPR1L = (uint8)(pwm_period >> 2);
        }
        else if (ccp->ccpx == CCP2_INST){
            CCP2CONbits.DC2B = (uint8)(pwm_period & 0x0003);
        CCPR2L = (uint8)(pwm_period >> 2);
        }
        else{/* Nothing */}
    }
    return ret;
}
std_ReturnType CCP_PWM_Start(const ccp_t* ccp){
    std_ReturnType ret = E_OK;
    if(ccp == NULL){
        ret = E_NOT_OK;
    }
    else{
        if(ccp->ccpx == CCP1_INST){
        CCP1CONbits.CCP1M = CCP_PWM;
        }
        else if (ccp->ccpx == CCP2_INST){
         CCP2CONbits.CCP2M = CCP_PWM;
        }
        else{/* Nothing */}
    }
    return ret;
}
std_ReturnType CCP_PWM_Stop(const ccp_t* ccp){
    std_ReturnType ret = E_OK;
    if(ccp == NULL){
        ret = E_NOT_OK;
    }
    else{
        if(ccp->ccpx == CCP1_INST){
        CCP1CONbits.CCP1M = CCP_PWM_COMPARE_CAPTURE_DISABLE;
        }
        else if (ccp->ccpx == CCP2_INST){
         CCP2CONbits.CCP2M = CCP_PWM_COMPARE_CAPTURE_DISABLE;
        }
        else{/* Nothing */}
    }
    return ret;
}
#endif


static std_ReturnType CCP_Interrupt_Config(const ccp_t* ccp){
#if CCP1_INTERRUPT == INTERRUPT_ENABLED
    CCP1_INTERRUPT_ENABLE();
    CCP1_CLEAR_FLAG();
    Interrupt_Handler_CCP1 = ccp->Interrupt_CCP1_Handler;
#if INETRRUPT_PRIORITY
    INTERRUPT_PRIORITY_ENABLED();
    if(ccp->ccp1_priority == HIGH_PRIORITY){
        INTERRUPT_HIGH_PRIORITY_INTERRUPT_ENABLED();
        CCP1_HIGH_PRIORITY();
    }
    else if(ccp->ccp1_priority == LOW_PRIORITY){
        INTERRUPT_LOW_PRIORITY_INTERRUPT_ENABLED();
        CCP1_LOW_PRIORITY();
    }
    else{/* Nothing */}
#else
    INTERRUPT_GLOBAL_INTERRUPT_ENABLED();
    INTERRUPT_PERIPHERAL_ENABLED();
#endif
#endif
    
    #if CCP2_INTERRUPT == INTERRUPT_ENABLED
    CCP2_INTERRUPT_ENABLE();
    CCP2_CLEAR_FLAG();
    Interrupt_Handler_CCP2 = ccp->Interrupt_CCP2_Handler;
#if INETRRUPT_PRIORITY
    INTERRUPT_PRIORITY_ENABLED();
    if(ccp->ccp2_priority == HIGH_PRIORITY){
        INTERRUPT_HIGH_PRIORITY_INTERRUPT_ENABLED();
        CCP2_HIGH_PRIORITY();
    }
    else if(ccp->ccp2_priority == LOW_PRIORITY){
        INTERRUPT_LOW_PRIORITY_INTERRUPT_ENABLED();
        CCP2_LOW_PRIORITY();
    }
    else{/* Nothing */}
#else
    INTERRUPT_GLOBAL_INTERRUPT_ENABLED();
    INTERRUPT_PERIPHERAL_ENABLED();
#endif
#endif
    
}



static std_ReturnType CCP_Capture_Config(const ccp_t* ccp){
    std_ReturnType ret = E_OK;
    if(ccp == NULL){
        ret = E_NOT_OK;
    }
    else{
        if(ccp->timer == CCP1_CCP2_TIMER3 ){
            T3CONbits.T3CCP1 = 0;
            T3CONbits.T3CCP2 = 1;
        }
        else if(ccp->timer == CCP1_TIMER1_CCPN2_TIMER2){
            T3CONbits.T3CCP1 = 1;
            T3CONbits.T3CCP2 = 0;
        }
        else if(ccp->timer == CCP1_CCP2_TIMER1){
            T3CONbits.T3CCP1 = 0;
            T3CONbits.T3CCP2 = 0;
        }
        else{}
        
        
        if(ccp->ccpx == CCP1_INST){
            switch(ccp->variant){
                case CCP_CAPTURE_FAILING_EDGE : CCP1_MODE_SELECT(CCP_CAPTURE_FAILING_EDGE); break;
                case CCP_CAPTURE_RISING_EDGE : CCP1_MODE_SELECT(CCP_CAPTURE_RISING_EDGE); break;
                case CCP_CAPTURE_ON_4TH_RISING_EDGE : CCP1_MODE_SELECT(CCP_CAPTURE_ON_4TH_RISING_EDGE); break;
                case CCP_CAPTURE_ON_16TH_RISING_EDGE : CCP1_MODE_SELECT(CCP_CAPTURE_ON_16TH_RISING_EDGE); break;
                default : ret = E_NOT_OK;
            }
        }
        else if (ccp->ccpx == CCP2_INST){
             switch(ccp->variant){
                case CCP_CAPTURE_FAILING_EDGE : CCP2_MODE_SELECT(CCP_CAPTURE_FAILING_EDGE); break;
                case CCP_CAPTURE_RISING_EDGE : CCP2_MODE_SELECT(CCP_CAPTURE_RISING_EDGE); break;
                case CCP_CAPTURE_ON_4TH_RISING_EDGE : CCP2_MODE_SELECT(CCP_CAPTURE_ON_4TH_RISING_EDGE); break;
                case CCP_CAPTURE_ON_16TH_RISING_EDGE : CCP2_MODE_SELECT(CCP_CAPTURE_ON_16TH_RISING_EDGE); break;
                default : ret = E_NOT_OK;
            }
        }
        else{/* NOTHING*/}
    }
    return ret;
}



static std_ReturnType CCP_Compare_Config(const ccp_t* ccp){
    std_ReturnType ret = E_OK;
    if(ccp == NULL){
        ret = E_NOT_OK;
    }
    else{
        if(ccp->ccpx == CCP1_INST){
            switch(ccp->variant){
                case CCP_COMPARE : CCP1_MODE_SELECT(CCP_COMPARE); break;
                case CCP_COMPARE_PIN_GPIO_HIGH : CCP1_MODE_SELECT(CCP_COMPARE_PIN_GPIO_HIGH); break;
                case CCP_COMPARE_PIN_GPIO_LOW : CCP1_MODE_SELECT(CCP_COMPARE_PIN_GPIO_LOW); break;
                case CCP_COMPARE_GEN_INTERRUPT : CCP1_MODE_SELECT(CCP_COMPARE_GEN_INTERRUPT); break;
                case CCP_COMPARE_SPECIAL_EVENT : CCP1_MODE_SELECT(CCP_COMPARE_SPECIAL_EVENT); break;
                default : ret = E_NOT_OK;
            }
        }
        else if (ccp->ccpx == CCP2_INST){
             switch(ccp->variant){
                case CCP_COMPARE : CCP2_MODE_SELECT(CCP_COMPARE); break;
                case CCP_COMPARE_PIN_GPIO_HIGH : CCP2_MODE_SELECT(CCP_COMPARE_PIN_GPIO_HIGH); break;
                case CCP_COMPARE_PIN_GPIO_LOW : CCP2_MODE_SELECT(CCP_COMPARE_PIN_GPIO_LOW); break;
                case CCP_COMPARE_GEN_INTERRUPT : CCP2_MODE_SELECT(CCP_COMPARE_GEN_INTERRUPT); break;
                case CCP_COMPARE_SPECIAL_EVENT : CCP2_MODE_SELECT(CCP_COMPARE_SPECIAL_EVENT); break;
                default : ret = E_NOT_OK;
            }
        }
        else{/* NOTHING*/}
    }
    return ret;
}
static std_ReturnType CCP_PWM_Config(const ccp_t* ccp){
    std_ReturnType ret = E_OK;
    if(ccp == NULL){
        ret = E_NOT_OK;
    }
    else{
        PR2 = (uint8)(((float)(_XTAL_FREQ) / ((float)(ccp->timer2_pre_scaler) * (float)(ccp->timer2_postscaler) * 4.0 * (float)(ccp->pwm_freq))) - 1);
        if(ccp->ccpx == CCP1_INST){
            CCP1_MODE_SELECT(CCP_PWM);
        }
        else if (ccp->ccpx == CCP2_INST){
            CCP2_MODE_SELECT(CCP_PWM);
        }
        else{/* NOTHING */}
    }
    return ret;
}

void CCP1_ISR(void){
    CCP1_CLEAR_FLAG();
    if(Interrupt_Handler_CCP1){
        Interrupt_Handler_CCP1();
    }
    else{/* Nothing */}
}

void CCP2_ISR(void){
    CCP2_CLEAR_FLAG();
    if(Interrupt_Handler_CCP2){
        Interrupt_Handler_CCP2();
    }
    else{/* Nothing */}
}