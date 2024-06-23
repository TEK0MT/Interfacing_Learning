/* 
 * File:   ecu_button.h
 * Author: Mohamed Tarek
 *
 * Created on June 23, 2024, 6:16 PM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H
/*Section : includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
/* Section : Macro Declarations */



/* Section : Macro Functions Declarations */


/* Section : Data Type Declarations */
typedef enum{
    BUTTON_PRESSED,
    BUTTON_RELEASED
}button_status_t;

typedef enum{
    BUTTON_ACTIVE_HIGH = 0,
    BUTTON_ACTIVE_LOW
}button_connection_t;

typedef struct{
    pin_config_t pin;
    button_status_t button_state;
    button_connection_t connection;
}button_t;
/* Section : Function Declarations */
std_ReturnType button_initialize(const button_t *btn);
std_ReturnType button_read_state(const button_t *btn,button_status_t *btn_state);

#endif	/* ECU_BUTTON_H */

