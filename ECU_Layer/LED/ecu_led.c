/* 
 * File:   ECU_LED.c
 * Author: MOHAMED TAREK
 *
 * Created on April 22, 2024, 6:04 AM
 */
#include "ecu_led.h"
/**
 * @brief Initialize led pin 
 * @param led is a pointer to a led pin
 * @return std_RetuenType
 */
std_ReturnType led_initialize(const led_t *led){
    std_ReturnType ret = E_OK;
    if(led == NULL){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = {.port = led->port_name, .pin = led->pin_name,
                                .direction = GPIO_DIRECTION_OUTPUT, .logic = led->led_status};
        gpio_pin_initialize(&pin_obj);
    }
    return ret;
}
/**
 * 
 * @param led
 * @return 
 */
std_ReturnType led_turn_on(const led_t *led){
    std_ReturnType ret = E_OK;
    if(led == NULL){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = {.port = led->port_name, .pin = led->pin_name,
                                .direction = GPIO_DIRECTION_OUTPUT, .logic = led->led_status};
        gpio_pin_write_logic(&pin_obj,GPIO_HIGH);
    }
    return ret;
}
std_ReturnType led_turn_off(const led_t *led){
    std_ReturnType ret = E_OK;
    if(led == NULL){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = {.port = led->port_name, .pin = led->pin_name,
                                .direction = GPIO_DIRECTION_OUTPUT, .logic = led->led_status};
        gpio_pin_write_logic(&pin_obj,GPIO_LOW);
    }
    return ret;
}
std_ReturnType led_turn_toggle(const led_t *led){
    std_ReturnType ret = E_OK;
    if(led == NULL){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = {.port = led->port_name, .pin = led->pin_name,
                                .direction = GPIO_DIRECTION_OUTPUT, .logic = led->led_status};
        gpio_pin_toggle_logic(&pin_obj);
    }
    return ret;
}