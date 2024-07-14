 /* 
 * File:   application.c
 * Author: MOHAMED TAREK
 *
 * Created on April 22, 2024, 5:31 AM
 */


#include "application.h"
void int0_isr(void){
    led_turn_toggle(&led1);
}
void int1_isr(void){
    led_turn_toggle(&led2);
}
void int2_isr(void){
    led_turn_toggle(&led3);
}
interrupt_Intx_t int0 = {.EXT_INTERRUPT_HANDLER = int0_isr,.intx = INTX0,.edge = Rising_Edge,.priority = HIGH_PRIORITY,.pin.port = PORTB_INDEX,.pin.pin = PIN0,.pin.logic = GPIO_DIRECTION_INPUT,.pin.logic = GPIO_LOW};
interrupt_Intx_t int1 = {.EXT_INTERRUPT_HANDLER = int1_isr,.intx = INTX1,.edge = Falling_Edge,.priority = HIGH_PRIORITY,.pin.port = PORTB_INDEX,.pin.pin = PIN1,.pin.logic = GPIO_DIRECTION_INPUT,.pin.logic = GPIO_HIGH};
interrupt_Intx_t int2 = {.EXT_INTERRUPT_HANDLER = int2_isr,.intx = INTX2,.edge = Rising_Edge,.priority = HIGH_PRIORITY,.pin.port = PORTB_INDEX,.pin.pin = PIN2,.pin.logic = GPIO_DIRECTION_INPUT,.pin.logic = GPIO_LOW};


std_ReturnType ret = E_NOT_OK;

int main() {

    application_initialize();
    Interrupt_INTx_Init(&int0);
    Interrupt_INTx_Init(&int1);
    Interrupt_INTx_Init(&int2);
    
    while(1){
        
        
        //counter++;
        
    }
    return (EXIT_SUCCESS);
}
void application_initialize(){
    ret = Ecu_initialize();
}
