/* 
 * File:   ecu_seven_segment.h
 * Author: Mohamed Tarek
 *
 * Created on July 1, 2024, 5:37 AM
 */

#ifndef ECU_SEVEN_SEGMENT_H
#define	ECU_SEVEN_SEGMENT_H
/*Section : includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_seven_segment_cfg.h"
/* Section : Macro Declarations */



/* Section : Macro Functions Declarations */


/* Section : Data Type Declarations */
typedef enum{
    SEV_SEGMENT_ANODE,
    SEV_SEGMENT_CATHOD
}sev_SEGMENT_TYPE;


typedef struct{
    pin_config_t pins[4];
    sev_SEGMENT_TYPE type;
}sev_seg_t;
/* Section : Function Declarations */
std_ReturnType sev_seg_initialize(const sev_seg_t *seg);
std_ReturnType sev_seg_write_number(const sev_seg_t *seg,uint8 number);

#endif	/* ECU_SEVEN_SEGMENT_H */

