/* 
 * File:   mcal_interrupt_config.h
 * Author: Mohamed Tarek
 *
 * Created on July 13, 2024, 8:49 AM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H
/*Section : includes */
#include "pic18f4620.h"
#include "../std_libraries.h"
#include "mcal_interrupt_gen_cfg.h"
#include "../GPIO/hal_gpio.h"
/* Section : Macro Declarations */
#define INTERRUPT_ENABLED       1
#define INTERRUPT_DISABLED      0
#define INTERRUPT_OCCURED       1
#define INTERRUPT_NOT_OCCURED   0
#define INTERRUPT_PRIORITY_ON   1
#define INTERRUPT_PRIORITY_OFF  0

/* Section : Macro Functions Declarations */
#if INETRRUPT_PRIORITY==1
#define INTERRUPT_PRIORITY_ENABLED()  (RCONbits.IPEN = 1)
#define INTERRUPT_PRIORITY_DISABLED()  (RCONbits.IPEN = 0)

#define INTERRUPT_HIGH_PRIORITY_INTERRUPT_ENABLED()     (INTCONbits.GIEH = 1)
#define INTERRUPT_HIGH_PRIORITY_INTERRUPT_DISABLED()    (INTCONbits.GIEH = 0)

#define INTERRUPT_LOW_PRIORITY_INTERRUPT_ENABLED()     (INTCONbits.GIEL = 1)
#define INTERRUPT_LOW_PRIORITY_INTERRUPT_DISABLED()     (INTCONbits.GIEL = 0)

#else
#define INTERRUPT_GLOBAL_INTERRUPT_ENABLED()     (INTCONbits.GIEH = 1)
#define INTERRUPT_GLOBAL_INTERRUPT_DISABLED()    (INTCONbits.GIEH = 0)
#define INTERRUPT_PERIPHERAL_ENABLED()     (INTCONbits.PEIE = 1)
#define INTERRUPT_PERIPHERAL_DISABLED()     (INTCONbits.PEIE = 0)
#endif

/* Section : Data Type Declarations */
typedef enum{
    LOW_PRIORITY = 0,
    HIGH_PRIORITY
}intx_priority;


/* Section : Function Declarations */


#endif	/* MCAL_INTERRUPT_CONFIG_H */

