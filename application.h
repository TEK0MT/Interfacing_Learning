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

  const uint8 customChar[] = {
  0x0E,
  0x0A,
  0x11,
  0x11,
  0x11,
  0x11,
  0x1F,
  0x00
};
const uint8 customChar2[] = {
  0x0E,
  0x0A,
  0x11,
  0x11,
  0x11,
  0x1F,
  0x1F,
  0x00
};
const const uint8 customChar3[] = {
  0x0E,
  0x0A,
  0x11,
  0x11,
  0x1F,
  0x1F,
  0x1F,
  0x00
};
const uint8 customChar4[] = {
  0x0E,
  0x0A,
  0x11,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x00
};
const uint8 customChar5[] = {
  0x0E,
  0x0A,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x00
};
const uint8 customChar6[] = {
  0x0E,
  0x0E,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x00
};
const uint8 customChar7[] = {
  0x04,
  0x0A,
  0x04,
  0x04,
  0x04,
  0x0E,
  0x15,
  0x0E
};
/* Section : Function Declarations */
void application_initialize();

#endif	/* APPLICATION_H */

