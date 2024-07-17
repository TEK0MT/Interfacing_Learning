/* 
 * File:   hal_eeprom.h
 * Author: Mohamed Tarek
 *
 * Created on July 17, 2024, 5:32 AM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H
/*Section : includes */
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../Interrupt/mcal_interrupt_config.h"
/* Section : Macro Declarations */
#define ACCESS_EEPROM_DATA  0
#define ACCESS_FLASH_DATA   1
#define ACCESS_FLASH_EEPROM_DATA 0
#define ALLOW_WRITE_CYCLE   1
#define INHIBIT_WRITE_CYCLE 0
#define WRITE_ON_EEPROM     1
#define READ_OFF_EEPROM     1

/* Section : Macro Functions Declarations */


/* Section : Data Type Declarations */



/* Section : Software Interfacing */
std_ReturnType WRITE_DATA_EEPROM(uint16 add,uint8 data);
std_ReturnType READ_DATA_EEPROM(uint16 add,uint8 *data);
#endif	/* HAL_EEPROM_H */

