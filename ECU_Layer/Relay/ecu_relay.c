/* 
 * File:   ecu_relay.h
 * Author: Mohamed Tarek
 *
 * Created on June 24, 2024, 10:09 PM
 */
#include "ecu_relay.h"
std_ReturnType relay_initialization(const relay_t *relay){
    std_ReturnType ret = E_OK;
    if(relay == NULL){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = {.port = relay->port, .pin = relay->pin,
                                .direction = GPIO_DIRECTION_OUTPUT, .logic = relay->status};
        gpio_pin_initialize(&pin_obj);
    }
    return ret;
}
std_ReturnType relay_turn_on(const relay_t *relay){
    std_ReturnType ret = E_OK;
    if(relay == NULL){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = {.port = relay->port, .pin = relay->pin,
                                .direction = GPIO_DIRECTION_OUTPUT, .logic = relay->status};
        gpio_pin_write_logic(&pin_obj,GPIO_HIGH);
    }
    return ret;
}
std_ReturnType relay_turn_off(const relay_t *relay){
    std_ReturnType ret = E_OK;
    if(relay == NULL){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = {.port = relay->port, .pin = relay->pin,
                                .direction = GPIO_DIRECTION_OUTPUT, .logic = relay->status};
        gpio_pin_write_logic(&pin_obj,GPIO_LOW);
    return ret;
}
}