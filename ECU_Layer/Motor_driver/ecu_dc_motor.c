/* 
 * File:   ecu_dc_motor.c
 * Author: Mohamed Tarek
 *
 * Created on June 26, 2024, 7:28 AM
 */
#include "ecu_dc_motor.h"
std_ReturnType motor_initialize(const dc_motor_t *motor){
    std_ReturnType ret = E_OK;
    if(motor == NULL){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_initialize(&(motor->dc_motor_pin[MOTORPIN0]));
        gpio_pin_initialize(&(motor->dc_motor_pin[MOTORPIN1]));
    }
    return ret;
}
std_ReturnType motor_turn_right(const dc_motor_t *motor){
    std_ReturnType ret = E_OK;
    if(motor == NULL){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(motor->dc_motor_pin[MOTORPIN0]),GPIO_HIGH);
        gpio_pin_write_logic(&(motor->dc_motor_pin[MOTORPIN1]),GPIO_LOW);
    }
    return ret;
}
std_ReturnType motor_turn_left(const dc_motor_t *motor){
    std_ReturnType ret = E_OK;
    if(motor == NULL){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(motor->dc_motor_pin[MOTORPIN1]),GPIO_HIGH);
        gpio_pin_write_logic(&(motor->dc_motor_pin[MOTORPIN0]),GPIO_LOW);
    }
    return ret;
}
std_ReturnType motor_stop(const dc_motor_t *motor){
    std_ReturnType ret = E_OK;
    if(motor == NULL){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(motor->dc_motor_pin[MOTORPIN1]),GPIO_LOW);
        gpio_pin_write_logic(&(motor->dc_motor_pin[MOTORPIN0]),GPIO_LOW);
    }
    return ret;
}