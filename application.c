/* 
 * File:   application.c
 * Author: MOHAMED TAREK
 *
 * Created on April 22, 2024, 5:31 AM
 */


#include "application.h"
dc_motor_t motor1 = {.dc_motor_pin[0].port = PORTA_INDEX,.dc_motor_pin[0].pin = PIN0,.dc_motor_pin[0].direction = GPIO_DIRECTION_OUTPUT,.dc_motor_pin[0].logic=GPIO_LOW,
                    .dc_motor_pin[1].port = PORTA_INDEX,.dc_motor_pin[1].pin = PIN1,.dc_motor_pin[1].direction = GPIO_DIRECTION_OUTPUT,.dc_motor_pin[1].logic=GPIO_LOW};
dc_motor_t motor2 = {.dc_motor_pin[0].port = PORTA_INDEX,.dc_motor_pin[0].pin = PIN2,.dc_motor_pin[0].direction = GPIO_DIRECTION_OUTPUT,.dc_motor_pin[0].logic=GPIO_LOW,
                    .dc_motor_pin[1].port = PORTA_INDEX,.dc_motor_pin[1].pin = PIN3,.dc_motor_pin[1].direction = GPIO_DIRECTION_OUTPUT,.dc_motor_pin[1].logic=GPIO_LOW};

std_ReturnType ret = E_NOT_OK;
int main() {
    application_initialize();
    while(1){
        motor_turn_right(&motor1);
        motor_turn_right(&motor2);
        __delay_ms(2000);
        motor_turn_left(&motor1);
        motor_turn_left(&motor2);
        __delay_ms(2000);
        motor_turn_right(&motor1);
        motor_turn_left(&motor2);
        __delay_ms(2000);
        motor_turn_left(&motor1);
        motor_turn_right(&motor2);
        __delay_ms(2000);
        motor_stop(&motor1);
        motor_stop(&motor2);
        __delay_ms(2000);
    }
    return (EXIT_SUCCESS);
}
void application_initialize(){
    ret = motor_initialize(&motor1);
    ret = motor_initialize(&motor2);
}
