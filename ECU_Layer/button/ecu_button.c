/* 
 * File:   ecu_button.c
 * Author: Mohamed Tarek
 *
 * Created on June 23, 2024, 6:16 PM
 */
#include "ecu_button.h"
std_ReturnType button_initialize(const button_t *btn)
{
    std_ReturnType ret = E_OK;
    if(btn == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_direction_intialize(&(btn->pin));
    }
    return ret;
}
std_ReturnType button_read_state(const button_t *btn,button_status_t *btn_state){
    std_ReturnType ret = E_NOT_OK;
    logic_t pin_logic = GPIO_LOW;
    if(btn == NULL){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_read_logic(&(btn->pin),&pin_logic);
        if(btn->connection == BUTTON_ACTIVE_HIGH){
            if(pin_logic == GPIO_HIGH){
                *btn_state = BUTTON_PRESSED;
            }
            else{
                *btn_state = BUTTON_RELEASED;
            }
        }
        else if(btn->connection == BUTTON_ACTIVE_LOW){
            if(pin_logic == GPIO_HIGH){
                *btn_state = BUTTON_RELEASED;
            }
            else{
                *btn_state = BUTTON_PRESSED;
            }
        }
        else{/*nothing*/}
        ret = E_OK;
    }
    return ret;
}
