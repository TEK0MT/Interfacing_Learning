/* 
 * File:   hal_adc.c
 * Author: Mohamed Tarek
 *
 * Created on August 1, 2024, 8:14 AM
 */
#include "hal_adc.h"


static std_ReturnType ADC_Select_Voltage_Refrence(const adc_config_t *adc ,uint8 voltage);
static std_ReturnType ADC_Select_result_format(const adc_config_t *adc ,uint8 format);
static std_ReturnType ADC_Configure_Port(SELECT_ADC_CHANNEL channel);



std_ReturnType ADC_Init(const adc_config_t *adc ){
    std_ReturnType ret = E_OK;
    if(adc == NULL){
        ret = E_NOT_OK;
    }
    else{
        ADC_DISABLE();
        ADC_INTERRUPT_DISABLE();
        CLEAR_ADC_STATUS();
        USE_INTERNAL_VOLTAGE();
        ADCON2bits.ADCS = adc->time;
        ADCON2bits.ACQT = adc->tad;
        ADCON0bits.CHS = adc->channel;
        #if ADC_INTERRUPT
        INTERRUPT_GLOBAL_INTERRUPT_ENABLED();
        INTERRUPT_PERIPHERAL_ENABLED();
        ADC_INTERRUPT_ENABLE();
        #if INETRRUPT_PRIORITY
        switch(priority){
            case LOW_PRIORITY :
                ADC_LOW_PRIORITY();
                break;
            case HIGH_PRIORITY :
                ADC_HIGH_PRIORITY();
                break;
        }
        #endif
        #endif
        ADC_Configure_Port(adc->channel);
        ADC_Select_Voltage_Refrence(adc,adc->voltage_refrence);
        ADC_Select_result_format(adc,adc->result_format);
        
        ADC_ENABLE();
    }
    return ret;
}
std_ReturnType ADC_Disable(const adc_config_t *adc ){
    std_ReturnType ret = E_OK;
    if(adc == NULL){
        ret = E_NOT_OK;
    }
    else{
        ADC_DISABLE();
    }
    return ret;
}
std_ReturnType ADC_Select_Channel(const adc_config_t *adc ,uint8 channels){
    std_ReturnType ret = E_OK;
    if(adc == NULL){
        ret = E_NOT_OK;
    }
    else{
        ADCON0bits.CHS = channels;
        ADC_Configure_Port(adc->channel);
    }
    return ret;
}
std_ReturnType ADC_Start_Conversion(const adc_config_t *adc){
    std_ReturnType ret = E_OK;
    if(adc == NULL){
        ret = E_NOT_OK;
    }
    else{
        CLEAR_ADC_STATUS();
        START_ADC_STATUS();
    }
    return ret;
}
std_ReturnType ADC_ISConversion_Done(const adc_config_t *adc ,uint8 *status){
    std_ReturnType ret = E_OK;
    if(adc == NULL){
        ret = E_NOT_OK;
    }
    else{
        status = (uint8)(!(ADCON0bits.GO_nDONE));
    }
    return ret;
}
std_ReturnType ADC_Get_Conversion_Result(const adc_config_t *adc ,uint16 *result){
    std_ReturnType ret = E_OK;
    if(adc == NULL){
        ret = E_NOT_OK;
    }
    else{
        if(adc->result_format == RIGHT_JUSTIFIED){
            *result = (uint16)(ADRESL + (ADRESH << 8));
        }
        else if(adc->result_format == LEFT_JUSTIFIED){
            *result = (uint16)((ADRESL + (ADRESH << 8)) >> 6);
        }
        else{
            *result = (uint16)(ADRESL + (ADRESH << 8));
        }
    }
    return ret;
}
std_ReturnType ADC_Get_Conversion_Blocking(const adc_config_t *adc ,SELECT_ADC_CHANNEL channel,uint16 *result){
    std_ReturnType ret = E_OK;
    if(adc == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = ADC_Select_Channel(adc,channel);
        ret = ADC_Start_Conversion(adc);
        while(ADCON0bits.GO_nDONE);
        ret = ADC_Get_Conversion_Result(adc,result);
    }
    return ret;
}

std_ReturnType ADC_Start_Conversion_Interrupt(const adc_config_t *adc ,SELECT_ADC_CHANNEL channel){
    std_ReturnType ret = E_OK;
    if(adc == NULL){
        ret = E_NOT_OK;
    }
    else{
        CLEAR_ADC_STATUS();
        ADC_Select_Channel(adc,channel);
        ADC_Start_Conversion(adc);
    }
    return ret;
}
static std_ReturnType ADC_Select_Voltage_Refrence(const adc_config_t *adc ,uint8 voltage){
    std_ReturnType ret = E_OK;
    if(adc == NULL){
        ret = E_NOT_OK;
    }
    else{
        if(voltage == INTERNAL_ADC_VOLTAGE){
            USE_INTERNAL_VOLTAGE(); 
        }
        else if(voltage == EXTERNAL_ADC_VOLTAGE){
            USE_EXTERNAL_VOLTAGE();
        }
        else{ret = E_NOT_OK;}
    }
    return ret;
}
static std_ReturnType ADC_Select_result_format(const adc_config_t *adc ,uint8 format){
    std_ReturnType ret = E_OK;
    if(adc == NULL){
        ret = E_NOT_OK;
    }
    else{
        if(format == RIGHT_JUSTIFIED){
            ADCON2bits.ADFM = 1; 
        }
        else if(format == LEFT_JUSTIFIED){
            ADCON2bits.ADFM = 0;
        }
        else{ADCON2bits.ADFM = 1;}
    }
    return ret;
}
static std_ReturnType ADC_Configure_Port(SELECT_ADC_CHANNEL channel){
    std_ReturnType ret = E_OK;
        switch(channel){
            case A0_ANALOG: SET_BIT(TRISA,_TRISA_RA0_POSITION); break;
            case A1_ANALOG: SET_BIT(TRISA,_TRISA_RA1_POSITION); break;
            case A2_ANALOG: SET_BIT(TRISA,_TRISA_RA2_POSITION); break;
            case A3_ANALOG: SET_BIT(TRISA,_TRISA_RA3_POSITION); break;
            case A4_ANALOG: SET_BIT(TRISA,_TRISA_RA5_POSITION); break;
            case A5_ANALOG: SET_BIT(TRISE,_TRISE_RE0_POSITION); break;
            case A6_ANALOG: SET_BIT(TRISE,_TRISE_RE1_POSITION); break;
            case A7_ANALOG: SET_BIT(TRISE,_TRISE_RE2_POSITION); break;
            case A8_ANALOG: SET_BIT(TRISB,_TRISB_RB2_POSITION); break;
            case A9_ANALOG: SET_BIT(TRISB,_TRISB_RB3_POSITION); break;
            case A10_ANALOG: SET_BIT(TRISB,_TRISB_RB1_POSITION); break;
            case A11_ANALOG: SET_BIT(TRISB,_TRISB_RB4_POSITION); break;
            case A12_ANALOG: SET_BIT(TRISB,_TRISB_RB0_POSITION); break;
        }
    
    return ret;
}