/* 
 * File:   application.c
 * Author: MOHAMED TAREK
 *
 * Created on April 22, 2024, 5:31 AM
 */


#include "application.h"
led_t led1 = {.port_name = PORTC_INDEX, .pin_name = PIN0, .led_status = LED_ON};
led_t led2 = {.port_name = PORTC_INDEX, .pin_name = PIN1, .led_status = LED_ON};

button_t btn1 = {.pin.port=PORTC_INDEX, .pin.pin = PIN2, .pin.direction = GPIO_DIRECTION_INPUT, .pin.logic = GPIO_LOW,
.connection = BUTTON_ACTIVE_HIGH, .button_state = BUTTON_RELEASED};
button_t btn2 = {.pin.port=PORTD_INDEX, .pin.pin = PIN0, .pin.direction = GPIO_DIRECTION_INPUT, .pin.logic = GPIO_LOW,
.connection = BUTTON_ACTIVE_LOW, .button_state = BUTTON_RELEASED};

std_ReturnType ret = E_NOT_OK;
int main() {
    application_initialize();
    while(1){
        button_read_state(&btn1,&(btn1.button_state));
        button_read_state(&btn2,&(btn2.button_state));
        if(btn1.button_state == BUTTON_PRESSED){
            ret = led_turn_on(&led1);
        }
        else{
            ret = led_turn_off(&led1);
        }
        if(btn2.button_state == BUTTON_PRESSED){
            ret = led_turn_off(&led2);
        }
        else{
            ret = led_turn_on(&led2);
        }
        
        __delay_ms(500);
    }
    return (EXIT_SUCCESS);
}
void application_initialize(){
    ret = led_initialize(&led1);
    ret = led_initialize(&led2);
    ret = button_initialize(&btn1);
    ret = button_initialize(&btn2);
    
    
}
