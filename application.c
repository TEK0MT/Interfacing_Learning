 /* 
 * File:   application.c
 * Author: MOHAMED TAREK
 *
 * Created on April 22, 2024, 5:31 AM
 */


#include "application.h"
std_ReturnType ret = E_NOT_OK;
void isr(void){
    led_turn_toggle(&led1);
}
timer3_t timer = {.TIMER3_HANDLER = isr,.prescaler_val = TIMER3_PRESCALER_DIV_8,.prevalue = 15536,.mode = TIMER3_COUNTER,.size = TIMER3_16BIT_OP};
uint8 value = 0;
int main() {
    application_initialize();
    TIMER3_INIT(&timer);
    
    
    while(1){
        TIMER3_Read_Value(&timer,&value);
    }
    return (EXIT_SUCCESS);
}
void application_initialize(){
    ret = Ecu_initialize();
}
