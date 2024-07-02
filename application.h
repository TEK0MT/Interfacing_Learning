/* 
 * File:   application.h
 * Author: MOHAMED TAREK
 *
 * Created on April 22, 2024, 6:06 AM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H
/*Section : includes */
#include "ECU_Layer/ECU_LAYER.h"
/* Section : Macro Declarations */


/* Section : Macro Functions Declarations */


/* Section : Data Type Declarations */
extern keypad_t keypad1;
extern led_t led1;

/* Section : Function Declarations */
void application_initialize();

#endif	/* APPLICATION_H */

