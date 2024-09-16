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
#include "MCAL_Layer/Interrupt/mcal_external_interrupt.h"
#include "MCAL_Layer/EEPROM/hal_eeprom.h"
#include "MCAL_Layer/ADC/hal_adc.h"
#include "MCAL_Layer/TIMERS/TIMER0/hal_timer0.h"
#include "MCAL_Layer/TIMERS/TIMER1/hal_timer1.h"
#include "MCAL_Layer/TIMERS/TIMER2/hal_timer2.h"
#include "MCAL_Layer/TIMERS/TIMER3/hal_timer3.h"
#include "MCAL_Layer/CCP/hal_cpp.h"
#include "MCAL_Layer/ESUART/hal_suart.h"
#include "MCAL_Layer/I2C/hal_i2c.h"
#include "MCAL_Layer/SPI/hal_spi.h"
/* Section : Macro Declarations */


/* Section : Macro Functions Declarations */


/* Section : Data Type Declarations */
extern keypad_t keypad1;
extern led_t led1;
extern led_t led2;
extern led_t led3;
extern lcd_8bits_t lcd1;
extern lcd_8bits_t lcd3;
extern lcd_4bits_t lcd2;

  
/* Section : Function Declarations */
void application_initialize();

#endif	/* APPLICATION_H */

