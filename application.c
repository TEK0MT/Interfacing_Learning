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
timer0_t timer = {.TIMER0_HANDLER = isr,.mode = TIMER0_TIMER_MODE,.edge = TIMER0_RISING_EDGE_SELECT,.size = TIMER_16BIT,.prescaler = TRM_PRESCALER_ON,.prescaler_val = PRESCALER_DIV_32,.prevalue = 3036};
uint16 value = 0;
int main() {
    application_initialize();
    TIMER0_INIT(&timer);
    
    
    while(1){
        TIMER0_Read_Value(&timer,&value);
    }
    return (EXIT_SUCCESS);
}
void application_initialize(){
    ret = Ecu_initialize();
}
