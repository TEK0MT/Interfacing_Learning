 /* 
 * File:   application.c
 * Author: MOHAMED TAREK
 *
 * Created on April 22, 2024, 5:31 AM
 */


#include "application.h"
volatile uint8 counter = 0;

void isr(){
    if(counter == 0){
        counter++;
    }
    else{
        counter = 0;
    }
    WRITE_DATA_EEPROM(0x3FF,counter);
}


interrupt_Intx_t int0 = {.EXT_INTERRUPT_HANDLER = isr,.intx = INTX0,.edge = Rising_Edge,.priority = HIGH_PRIORITY,.pin.port = PORTB_INDEX,.pin.pin = PIN0,.pin.logic = GPIO_DIRECTION_INPUT,.pin.logic = GPIO_LOW};

std_ReturnType ret = E_NOT_OK;

int main() {

    application_initialize();
    Interrupt_INTx_Init(&int0);
    READ_DATA_EEPROM(0x3FF,&counter);
    
    while(1){
        if(!counter){
            led_turn_toggle(&led1);
            led_turn_off(&led2);
            __delay_ms(250);
        }
        else{
            led_turn_toggle(&led2);
            led_turn_off(&led1);
            __delay_ms(500);
        }
        
    }
    return (EXIT_SUCCESS);
}
void application_initialize(){
    ret = Ecu_initialize();
}
