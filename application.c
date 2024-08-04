 /* 
 * File:   application.c
 * Author: MOHAMED TAREK
 *
 * Created on April 22, 2024, 5:31 AM
 */


#include "application.h"
std_ReturnType ret = E_NOT_OK;
adc_config_t adc1 = {.channel = CHANNEL0,.voltage_refrence = 0,.time = FOSC_DIV_16,.tad = TAD12,.result_format = RIGHT_JUSTIFIED};
uint16 value = 0;
int main() {
ADC_Init(&adc1);
    
    
    while(1){
        ADC_Get_Conversion_Blocking(&adc1,CHANNEL0,&value);
    }
    return (EXIT_SUCCESS);
}
void application_initialize(){
    ret = Ecu_initialize();
}
