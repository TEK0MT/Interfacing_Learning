/* 
 * File:   hal_gpio.c
 * Author: MOHAMED TAREK
 *
 * Created on April 22, 2024, 5:43 AM
 */
#include "hal_gpio.h"
/*Reference to Data Direction Control Registers*/
volatile uint8 *tris_registers[] = {&TRISA,&TRISB,&TRISC,&TRISD,&TRISE};
/*Reference to Data Latch Registers(Read and Write to Data Latch)*/
volatile uint8 *lat_registers[] = {&LATA,&LATB,&LATC,&LATD,&LATE};
/*Reference to the Port Registers*/
volatile uint8 *port_registers[] = {&PORTA,&PORTB,&PORTC,&PORTD,&PORTE};

std_ReturnType gpio_pin_direction_intialize(const pin_config_t *_pin_config){
    std_ReturnType ret = E_OK;
    if(NULL == _pin_config){
        ret = E_NOT_OK;
    }
    else{
    switch(_pin_config->direction)
    {
        case GPIO_DIRECTION_OUTPUT :
            CLEAR_BIT(*tris_registers[_pin_config->port],_pin_config->pin);
            break;
        case GPIO_DIRECTION_INPUT :
            SET_BIT(*tris_registers[_pin_config->port],_pin_config->pin);
            break;
        default :
            ret = E_NOT_OK;
    }
    }
    return ret;
}
std_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config,direction_t *dic_status){
    std_ReturnType ret = E_OK;
    if(NULL == _pin_config || NULL == dic_status){
        ret = E_NOT_OK;
    }
    else{
        
    }
    return ret;
}
std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config,logic_t logic){
    std_ReturnType ret = E_OK;
    if(NULL == _pin_config){
        ret = E_NOT_OK;
    }
    else{
        
    }
    return ret;
}
std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config,logic_t *logic){
    std_ReturnType ret = E_OK;
    if(NULL == _pin_config || NULL == logic){
        ret = E_NOT_OK;
    }
    else{
        
    }
    return ret;
}
std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config){
    std_ReturnType ret = E_OK;
    if(NULL == _pin_config ){
        ret = E_NOT_OK;
    }
    else{
        
    }
    return ret;
}


std_ReturnType gpio_port_direction_intialize(const port_index_t port,uint8 direction){
    std_ReturnType ret = E_OK;
    return ret;
}
std_ReturnType gpio_port_get_direction_status(const port_index_t port,uint8 *direction_status){
    std_ReturnType ret = E_OK;
    if(NULL == direction_status){
        ret = E_NOT_OK;
    }
    else{
        
    }
    return ret;
}
std_ReturnType gpio_port_read_logic(const port_index_t port,uint8 *logic){
    std_ReturnType ret = E_OK;
    if(NULL == logic){
        ret = E_NOT_OK;
    }
    else{
        
    }
    return ret;
}
std_ReturnType gpio_port_write_logic(const port_index_t port,uint8 logic){
    std_ReturnType ret = E_OK;
    return ret;
}
std_ReturnType gpio_port_toggle_logic(const port_index_t port){
    std_ReturnType ret = E_OK;
    return ret;
}