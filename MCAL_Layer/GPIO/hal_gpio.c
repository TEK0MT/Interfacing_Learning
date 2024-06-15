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

#if PORT_PIN_CONFIGURATION == 0x01
/**
 * @brief initialize pin configuration
 * @param _pin_config   @ref pin_config_t
 * @return standard type
 */
std_ReturnType gpio_pin_direction_intialize(const pin_config_t *_pin_config){
    std_ReturnType ret = E_OK;
    if(NULL == _pin_config || _pin_config->pin > MAX_GPIO_PINS - 1){
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
#endif
/**
 * @brief get if the pin is input or outupt
 * @param _pin_config @ref pin_config_t
 * @param dic_status @ref direction_t
 * @return standard type
 */
#if PORT_PIN_CONFIGURATION==0x01
std_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config,direction_t *dic_status){
    std_ReturnType ret = E_OK;
    if(NULL == _pin_config || NULL == dic_status){
        ret = E_NOT_OK;
    }
    else{
        *dic_status = READ_BIT(*tris_registers[_pin_config->port],_pin_config->pin);
    }
    return ret;
}
#endif

#if PORT_PIN_CONFIGURATION == 1
/**
 * @brief supply 5v or not to the pin
 * @param _pin_config @ref pin_config_t
 * @param logic @ref logic_t
 * @return standard type
 */
std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config,logic_t logic){
    std_ReturnType ret = E_OK;
    if(NULL == _pin_config){
        ret = E_NOT_OK;
    }
    else{
        switch(logic){
            case GPIO_LOW :
                CLEAR_BIT(*lat_registers[_pin_config->port],_pin_config->pin);
                break;
            case GPIO_HIGH :
                SET_BIT(*lat_registers[_pin_config->port],_pin_config->pin);
                break;
            default:
                break;
                
        }
    }
    return ret;
}
#endif

#if PORT_PIN_CONFIGURATION == 1
/**
 * @brief read whether the pin has 5v or not
 * @param _pin_config @ref pin_config_t
 * @param logic @ref logic_t
 * @return standard type
 */
std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config,logic_t *logic){
    std_ReturnType ret = E_OK;
    if(NULL == _pin_config || NULL == logic){
        ret = E_NOT_OK;
    }
    else{
        *logic = READ_BIT(*port_registers[_pin_config->port],_pin_config->pin);

    }
    return ret;
}
#endif

#if PORT_PIN_CONFIGURATION == 1
/**
 * @brief change the output of the pin
 * @param _pin_config @ref pin_config_t
 * @return standard type
 */
std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config){
    std_ReturnType ret = E_OK;
    if(NULL == _pin_config ){
        ret = E_NOT_OK;
    }
    else{
        
    }
    return ret;
}
#endif

#if PORT_PIN_CONFIGURATION == 1
/**
 * 
 * @param _pin_config
 * @return standard type
 */
std_ReturnType gpio_pin_initialize(const pin_config_t *_pin_config){
    std_ReturnType ret = E_OK;
    if(NULL == _pin_config ){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_direction_intialize(_pin_config);
        gpio_pin_write_logic(_pin_config,_pin_config->logic);
    }
    return ret;
}
#endif

#if PORT_CONFIGURATION == 1
/**
 * @brief initialize port direction
 * @param port @ref port_index_t
 * @param direction @ref direction_t
 * @return standard type
 */
std_ReturnType gpio_port_direction_initialize(const port_index_t port,direction_t direction){
    std_ReturnType ret = E_OK;
    if(port > MAX_PORT - 1){
        ret = E_NOT_OK;
    }
    else{
        *tris_registers[port] = direction;
    }
    return ret;
}
#endif

#if PORT_CONFIGURATION == 1
/**
 * @brief get if the port is input or output
 * @param port @ref port_index_t
 * @param direction_status @ref direction_t
 * @return standard type
 */
std_ReturnType gpio_port_get_direction_status(const port_index_t port,direction_t *direction_status){
    std_ReturnType ret = E_OK;
    if(NULL == direction_status || port > MAX_PORT - 1){
        ret = E_NOT_OK;
    }
    else{
        *direction_status = tris_registers[port];
    }
    return ret;
}
#endif

#if PORT_CONFIGURATION == 1
/**
 * @brief read if the port is on or off
 * @param port @ref port_index_t
 * @param logic @ref logic_t
 * @return standard type
 */
std_ReturnType gpio_port_read_logic(const port_index_t port,uint8 *logic){
    std_ReturnType ret = E_OK;
    if(NULL == logic || port > MAX_PORT - 1){
        ret = E_NOT_OK;
    }
    else{
        *logic = port_registers[port];
    }
    return ret;
}
#endif

#if PORT_CONFIGURATION == 1
/**
 * @brief write the logic of the port
 * @param port @ref port_index_t
 * @param logic @ref logic_t
 * @return standard type
 */
std_ReturnType gpio_port_write_logic(const port_index_t port,uint8 logic){
    std_ReturnType ret = E_OK;
    if(port > MAX_PORT - 1){
        ret = E_NOT_OK;
    }
    else{
        *lat_registers[port] = logic;
    }
    return ret;
}
#endif 

#if PORT_CONFIGURATION == 1
/**
 * @brief toglle port logic
 * @param port @ref port_index_t
 * @return standard type
 */
std_ReturnType gpio_port_toggle_logic(const port_index_t port){
    std_ReturnType ret = E_OK;
    if(port > MAX_PORT - 1){
        ret = E_NOT_OK;
    }
    else{
        *lat_registers[port] ^= PORT_MASK;
    }
    return ret;
}
#endif