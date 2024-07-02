/* 
 * File:   ECU_LAYER.h
 * Author: Mohamed Tarek
 *
 * Created on July 2, 2024, 2:04 AM
 */

#ifndef ECU_LAYER_H
/*Section : includes */
#include "LED/ecu_led.h"
#include "button/ecu_button.h"
#include "Relay/ecu_relay.h"
#include "Motor_driver/ecu_dc_motor.h"
#include "7_SEGMENT/ecu_seven_segment.h"
#include "Keypad/Keypad.h"
/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */


/* Section : Data Type Declarations */


/* Section : Function Declarations */
std_ReturnType Ecu_initialize(void);
#endif	/* ECU_LAYER_H */

