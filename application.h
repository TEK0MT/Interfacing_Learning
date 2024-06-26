/* 
 * File:   application.h
 * Author: MOHAMED TAREK
 *
 * Created on April 22, 2024, 6:06 AM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H
/*Section : includes */
#include "ECU_Layer/LED/ecu_led.h"
#include "ECU_Layer/button/ecu_button.h"
#include "ECU_Layer/Relay/ecu_relay.h"  
#include "ECU_Layer/Motor_driver/ecu_dc_motor.h"
/* Section : Macro Declarations */
#define _XTAL_FREQ 8000000UL


/* Section : Macro Functions Declarations */


/* Section : Data Type Declarations */


/* Section : Function Declarations */
void application_initialize();

#endif	/* APPLICATION_H */

