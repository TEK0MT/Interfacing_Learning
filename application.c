/* 
 * File:   application.c
 * Author: MOHAMED TAREK
 *
 * Created on April 22, 2024, 5:31 AM
 */


#include "application.h"
led_t led1 = {.port_name = PORTC_INDEX, .pin_name = PIN0, .led_status = LED_ON};
led_t led2 = {.port_name = PORTC_INDEX, .pin_name = PIN1, .led_status = LED_ON};
led_t led3 = {.port_name = PORTC_INDEX, .pin_name = PIN2, .led_status = LED_ON};
led_t led4 = {.port_name = PORTC_INDEX, .pin_name = PIN3, .led_status = LED_ON};

std_ReturnType ret = E_NOT_OK;
int main() {
    application_initialize();
    while(1){
        led_turn_toggle(&led1);
        led_turn_toggle(&led2);
        led_turn_toggle(&led3);
        led_turn_toggle(&led4);
        __delay_ms(500);
    }
    return (EXIT_SUCCESS);
}
void application_initialize(){
    ret = led_initialize(&led1);
    ret = led_initialize(&led2);
    ret = led_initialize(&led3);
    ret = led_initialize(&led4);
    
}
