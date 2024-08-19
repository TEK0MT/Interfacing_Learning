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
timer1_t timer = {.TIMER1_HANDLER = isr,.mode = TIMER1_TIMER,.size = TIMER1_16BIT_OP,.prescaler_val = TIMER1_PRESCALER_DIV_8,.prevalue = 15536};
uint16 value = 0;
int main() {
    application_initialize();
    TIMER1_INIT(&timer);
    
    
    while(1){
        TIMER1_Read_Value(&timer,&value);
    }
    return (EXIT_SUCCESS);
}
void application_initialize(){
    ret = Ecu_initialize();
}
