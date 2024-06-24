/* 
 * File:   ecu_relay.h
 * Author: Mohamed Tarek
 *
 * Created on June 24, 2024, 10:09 PM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H
/*Section : includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_relay_cfg.h"
/* Section : Macro Declarations */
#define RELAY_OFF_STATUS 0x00U
#define RELAY_ON_STATUS  0x01U


/* Section : Macro Functions Declarations */


/* Section : Data Type Declarations */


typedef struct{
    uint8 pin             : 4;
    uint8 port            : 3;
    uint8 status : 1;
}relay_t;

/* Section : Function Declarations */
std_ReturnType relay_initialization(const relay_t *relay);
std_ReturnType relay_turn_on(const relay_t *relay);
std_ReturnType relay_turn_off(const relay_t *relay);

#endif	/* ECU_RELAY_H */

