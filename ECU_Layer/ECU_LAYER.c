/* 
 * File:   ECU_LAYER.c
 * Author: Mohamed Tarek
 *
 * Created on July 2, 2024, 2:04 AM
 */
#include "ECU_LAYER.h"
keypad_t keypad1 = {.rows[0].port = PORTC_INDEX , .rows[0].pin = PIN0,.rows[0].logic = GPIO_LOW,.rows[0].direction = GPIO_DIRECTION_OUTPUT,
                    .rows[1].port = PORTC_INDEX , .rows[1].pin = PIN1,.rows[1].logic = GPIO_LOW,.rows[1].direction = GPIO_DIRECTION_OUTPUT,
                    .rows[2].port = PORTC_INDEX , .rows[2].pin = PIN2,.rows[2].logic = GPIO_LOW,.rows[2].direction = GPIO_DIRECTION_OUTPUT,
                    .rows[3].port = PORTC_INDEX , .rows[3].pin = PIN3,.rows[3].logic = GPIO_LOW,.rows[3].direction = GPIO_DIRECTION_OUTPUT,
                    .coloumns[0].port = PORTC_INDEX , .coloumns[0].pin = PIN4,.coloumns[0].logic = GPIO_LOW,.coloumns[0].direction = GPIO_DIRECTION_INPUT,
                    .coloumns[1].port = PORTC_INDEX , .coloumns[1].pin = PIN5,.coloumns[1].logic = GPIO_LOW,.coloumns[1].direction = GPIO_DIRECTION_INPUT,
                    .coloumns[2].port = PORTC_INDEX , .coloumns[2].pin = PIN6,.coloumns[2].logic = GPIO_LOW,.coloumns[2].direction = GPIO_DIRECTION_INPUT,
                    .coloumns[3].port = PORTC_INDEX , .coloumns[3].pin = PIN7,.coloumns[3].logic = GPIO_LOW,.coloumns[3].direction = GPIO_DIRECTION_INPUT,
};


lcd_8bits_t lcd1 = {.rs.port = PORTC_INDEX,.rs.pin = PIN5,.rs.logic = GPIO_LOW,.rs.logic=GPIO_DIRECTION_OUTPUT,
                    .enable.port = PORTC_INDEX,.enable.pin = PIN7,.enable.logic = GPIO_LOW,.enable.logic=GPIO_DIRECTION_OUTPUT,
                    .data_pins[0].port = PORTD_INDEX,.data_pins[0].pin = PIN0,.data_pins[0].logic=GPIO_LOW,.data_pins[0].direction=GPIO_DIRECTION_OUTPUT,
                    .data_pins[1].port = PORTD_INDEX,.data_pins[1].pin = PIN1,.data_pins[1].logic=GPIO_LOW,.data_pins[1].direction=GPIO_DIRECTION_OUTPUT,
                    .data_pins[2].port = PORTD_INDEX,.data_pins[2].pin = PIN2,.data_pins[2].logic=GPIO_LOW,.data_pins[2].direction=GPIO_DIRECTION_OUTPUT,
                    .data_pins[3].port = PORTD_INDEX,.data_pins[3].pin = PIN3,.data_pins[3].logic=GPIO_LOW,.data_pins[3].direction=GPIO_DIRECTION_OUTPUT,
                    .data_pins[4].port = PORTD_INDEX,.data_pins[4].pin = PIN4,.data_pins[4].logic=GPIO_LOW,.data_pins[4].direction=GPIO_DIRECTION_OUTPUT,
                    .data_pins[5].port = PORTD_INDEX,.data_pins[5].pin = PIN5,.data_pins[5].logic=GPIO_LOW,.data_pins[5].direction=GPIO_DIRECTION_OUTPUT,
                    .data_pins[6].port = PORTD_INDEX,.data_pins[6].pin = PIN6,.data_pins[6].logic=GPIO_LOW,.data_pins[6].direction=GPIO_DIRECTION_OUTPUT,
                    .data_pins[7].port = PORTD_INDEX,.data_pins[7].pin = PIN7,.data_pins[7].logic=GPIO_LOW,.data_pins[7].direction=GPIO_DIRECTION_OUTPUT};

lcd_4bits_t lcd2 = {.rs.port = PORTC_INDEX,.rs.pin = PIN0,.rs.logic = GPIO_LOW,.rs.logic=GPIO_DIRECTION_OUTPUT,
                    .enable.port = PORTC_INDEX,.enable.pin = PIN1,.enable.logic = GPIO_LOW,.enable.logic=GPIO_DIRECTION_OUTPUT,
                    .data_pins[0].port = PORTC_INDEX,.data_pins[0].pin = PIN2,.data_pins[0].logic=GPIO_LOW,.data_pins[0].direction=GPIO_DIRECTION_OUTPUT,
                    .data_pins[1].port = PORTC_INDEX,.data_pins[1].pin = PIN3,.data_pins[1].logic=GPIO_LOW,.data_pins[1].direction=GPIO_DIRECTION_OUTPUT,
                    .data_pins[2].port = PORTC_INDEX,.data_pins[2].pin = PIN4,.data_pins[2].logic=GPIO_LOW,.data_pins[2].direction=GPIO_DIRECTION_OUTPUT,
                    .data_pins[3].port = PORTC_INDEX,.data_pins[3].pin = PIN5,.data_pins[3].logic=GPIO_LOW,.data_pins[3].direction=GPIO_DIRECTION_OUTPUT
};

led_t led1 = {.port_name = PORTD_INDEX,.pin_name = PIN0,.led_status = LED_OFF};

std_ReturnType Ecu_initialize(void){
    //keypad_initialize(&keypad1);
   // led_initialize(&led1);
    lcd_8bit_initialize(&lcd1);
    //lcd_4bit_initialize(&lcd2);
}