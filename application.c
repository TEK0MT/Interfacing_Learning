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
timer2_t timer = {.TIMER2_HANDLER = isr,.prescaler_val = TIMER2_PRESCALER_DIV_4,.prevalue = 250,.postscale_val = TIMER2_POSTSCALER_DIV_BY_10};
uint8 value = 0;
int main() {
    application_initialize();
    TIMER2_INIT(&timer);
    
    
    while(1){
        TIMER2_Read_Value(&timer,&value);
    }
    return (EXIT_SUCCESS);
}
void application_initialize(){
    ret = Ecu_initialize();
}
