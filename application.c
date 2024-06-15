/* 
 * File:   application.c
 * Author: MOHAMED TAREK
 *
 * Created on April 22, 2024, 5:31 AM
 */


#include "application.h"
pin_config_t led1 ={
    .pin = PIN0,
    .port = PORTC_INDEX,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW
};
pin_config_t led2 ={
    .pin = PIN1,
    .port = PORTC_INDEX,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW
};
pin_config_t led3 ={
    .pin = PIN2,
    .port = PORTC_INDEX,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW
};

pin_config_t btn_1 = {
    .pin = PIN0,
    .port = PORTD_INDEX,
    .direction = GPIO_DIRECTION_INPUT,
    .logic = GPIO_LOW
};

logic_t btn_status = GPIO_LOW;

std_ReturnType ret = E_NOT_OK;
direction_t portc_direction;

int main() {
    application_initialize();
    while(1){
        ret = gpio_port_get_direction_status(PORTC_INDEX,&portc_direction);
        ret = gpio_port_write_logic(PORTC_INDEX,0xFF);
        __delay_ms(1000);
        ret = gpio_port_write_logic(PORTC_INDEX,GPIO_LOW);
        __delay_ms(1000);
    }
    return (EXIT_SUCCESS);
}
void application_initialize(){
    /*ret = gpio_pin_initialize(&led1);
    ret = gpio_pin_initialize(&led2);
    ret = gpio_pin_initialize(&led3);
    ret = gpio_pin_initialize(&btn_1);*/
    ret = gpio_port_direction_initialize(PORTC_INDEX,0x00);
    
}
