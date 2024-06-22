/* 
 * File:   ecu_led.h
 * Author: MOHAMED TAREK
 *
 * Created on April 22, 2024, 6:04 AM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H
/*Section : includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_led_cfg.h"
/* Section : Macro Declarations */


/* Section : Macro Functions Declarations */


/* Section : Data Type Declarations */
typedef enum{
    LED_OFF,
    LED_ON
}led_status_t;

typedef struct{
    uint8 port_name  : 3;
    uint8 pin_name   : 3;
    uint8 led_status : 1;
    uint8 Reserved   : 1;
}led_t;

/* Section : Function Declarations */
std_ReturnType led_initialize(const led_t *led);
std_ReturnType led_turn_on(const led_t *led);
std_ReturnType led_turn_off(const led_t *led);
std_ReturnType led_turn_toggle(const led_t *led);
#endif	/* ECU_LED_H */

