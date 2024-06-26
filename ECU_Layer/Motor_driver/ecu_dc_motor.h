/* 
 * File:   ecu_dc_motor.h
 * Author: Mohamed Tarek
 *
 * Created on June 26, 2024, 7:28 AM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H
/*Section : includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
/* Section : Macro Declarations */
#define DC_MOTOTR_ON 0x01
#define DC_MOTOTR_OFF 0x00

#define MOTORPIN0 0
#define MOTORPIN1 1


/* Section : Macro Functions Declarations */


/* Section : Data Type Declarations */
typedef struct{
    pin_config_t dc_motor_pin[2];
}dc_motor_t;

/* Section : Function Declarations */
std_ReturnType motor_initialize(const dc_motor_t *motor);
std_ReturnType motor_turn_right(const dc_motor_t *motor);
std_ReturnType motor_turn_left(const dc_motor_t *motor);
std_ReturnType motor_stop(const dc_motor_t *motor);
#endif	/* ECU_DC_MOTOR_H */

