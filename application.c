/* 
 * File:   application.c
 * Author: MOHAMED TAREK
 *
 * Created on April 22, 2024, 5:31 AM
 */


#include "application.h"

std_ReturnType ret = E_NOT_OK;
uint8 value = ZERO_INIT ;
int main() {
    application_initialize();
    while(1){
        ret = keypad_read_value(&keypad1,&value);
        if(value == '1'){
            led_turn_on(&led1);
            __delay_ms(1000);
            led_turn_off(&led1);
            __delay_ms(1000);
        }
        else if(value == '2'){
            led_turn_on(&led1);
            __delay_ms(500);
            led_turn_off(&led1);
            __delay_ms(500);
        }
        else if(value == '3'){
            led_turn_on(&led1);
            __delay_ms(100);
            led_turn_off(&led1);
            __delay_ms(100);
        }
        else if(value == '4'){
            led_turn_on(&led1);
        }
        else if(value == '5'){
            led_turn_off(&led1);
        }
        
    }
    return (EXIT_SUCCESS);
}
void application_initialize(){
    ret = Ecu_initialize();
}
