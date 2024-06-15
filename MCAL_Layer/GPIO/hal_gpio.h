/* 
 * File:   hal_gpio.h
 * Author: MOHAMED TAREK
 *
 * Created on April 22, 2024, 5:44 AM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/*Section : includes */
#include "hal_gpio_cfg.h"
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/device_config.h"
 /* Section : Macro Declarations */
#define BIT_MASK (uint8)1
#define MAX_GPIO_PINS 8
#define MAX_PORT 5

/* Section : Macro Functions Declarations */
#define HWREGB(_x) (*((volatile uint8*)(_x)))

#define SET_BIT(REG, BIT_POSITION)     (REG |= (BIT_MASK<<BIT_POSITION))
#define CLEAR_BIT(REG, BIT_POSITION)   (REG &= ~(BIT_MASK<<BIT_POSITION))
#define TOGGLE_BIT(REG, BIT_POSITION)  (REG ^= (BIT_MASK<<BIT_POSITION))
#define READ_BIT(REG, BIT_POSITION)    ((REG >> BIT_POSITION) & BIT_MASK)

/* Section : Data Type Declarations */
typedef enum{
    GPIO_LOW = 0,
    GPIO_HIGH
}logic_t;

typedef enum{
    GPIO_DIRECTION_OUTPUT = 0,
    GPIO_DIRECTION_INPUT
}direction_t;

typedef enum{
    PIN0 = 0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7
}pin_index_t;

typedef enum{
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX
}port_index_t;

typedef struct{
    uint8 port              :3;
    uint8 pin               :3;
    uint8 direction         :1;    
    uint8 logic             :1;
}pin_config_t;
/* Section : Function Declarartions */
std_ReturnType gpio_pin_direction_intialize(const pin_config_t *_pin_config);
std_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config,direction_t *dic_status);
std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config,logic_t logic);
std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config,logic_t *logic);
std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config);
std_ReturnType gpio_pin_initialize(const pin_config_t *_pin_config);


std_ReturnType gpio_port_direction_initialize(const port_index_t port,direction_t direction);
std_ReturnType gpio_port_get_direction_status(const port_index_t port,direction_t *direction_status);
std_ReturnType gpio_port_read_logic(const port_index_t port,uint8 *logic);
std_ReturnType gpio_port_write_logic(const port_index_t port,uint8 logic);
std_ReturnType gpio_port_toggle_logic(const port_index_t port);
#endif	/* HAL_GPIO_H */

