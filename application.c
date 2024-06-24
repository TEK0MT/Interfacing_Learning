/* 
 * File:   application.c
 * Author: MOHAMED TAREK
 *
 * Created on April 22, 2024, 5:31 AM
 */


#include "application.h"
relay_t relay = {.pin = PIN0,.port=PORTC_INDEX,.status = RELAY_OFF_STATUS};

std_ReturnType ret = E_NOT_OK;
int main() {
    application_initialize();
    while(1){
        relay_turn_on(&relay);
        __delay_ms(5000);
        relay_turn_off(&relay);
        __delay_ms(5000);
    }
    return (EXIT_SUCCESS);
}
void application_initialize(){
    ret = relay_initialization(&relay);
}
