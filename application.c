/* 
 * File:   application.c
 * Author: MOHAMED TAREK
 *
 * Created on April 22, 2024, 5:31 AM
 */


#include "application.h"
sev_seg_t seven = {.pins[0].direction = GPIO_DIRECTION_OUTPUT,.pins[0].logic=GPIO_HIGH,.pins[0].pin=PIN0,.pins[0].port=PORTC_INDEX,
                   .pins[1].direction = GPIO_DIRECTION_OUTPUT,.pins[1].logic=GPIO_HIGH,.pins[1].pin=PIN1,.pins[1].port=PORTC_INDEX,
                   .pins[2].direction = GPIO_DIRECTION_OUTPUT,.pins[2].logic=GPIO_HIGH,.pins[2].pin=PIN2,.pins[2].port=PORTC_INDEX,
                   .pins[3].direction = GPIO_DIRECTION_OUTPUT,.pins[3].logic=GPIO_HIGH,.pins[3].pin=PIN3,.pins[3].port=PORTC_INDEX,
                   .type = SEV_SEGMENT_ANODE
};
pin_config_t pin0 = {.direction = GPIO_DIRECTION_OUTPUT, .logic = GPIO_LOW,.pin = PIN0,.port=PORTD_INDEX};
pin_config_t pin1 = {.direction = GPIO_DIRECTION_OUTPUT, .logic = GPIO_LOW,.pin = PIN1,.port=PORTD_INDEX};

std_ReturnType ret = E_NOT_OK;
uint8 number = 45;

int main() {
    application_initialize();
    while(1){
        
        ret = sev_seg_write_number(&seven,(uint8)(number / 10));
        ret = gpio_pin_write_logic(&pin0,GPIO_HIGH);
        __delay_ms(5);
        ret = gpio_pin_write_logic(&pin0,GPIO_LOW);
        ret = sev_seg_write_number(&seven,(uint8)(number % 10));
        ret = gpio_pin_write_logic(&pin1,GPIO_HIGH);
        __delay_ms(5);
        ret = gpio_pin_write_logic(&pin1,GPIO_LOW);
        
    }
    return (EXIT_SUCCESS);
}
void application_initialize(){
    ret = sev_seg_initialize(&seven);
    ret = gpio_pin_initialize(&pin0);
    ret = gpio_pin_initialize(&pin1);
    
}
