/* 
 * File:   ecu_seven_segment.c
 * Author: Mohamed Tarek
 *
 * Created on July 1, 2024, 5:37 AM
 */
#include "ecu_seven_segment.h"
std_ReturnType sev_seg_initialize(const sev_seg_t *seg){
    std_ReturnType ret = E_OK;
    if(seg == NULL){
        ret = E_NOT_OK;
    }
    else{
        
        gpio_pin_initialize(&(seg->pins[0]));
        gpio_pin_initialize(&(seg->pins[1]));
        gpio_pin_initialize(&(seg->pins[2]));
        gpio_pin_initialize(&(seg->pins[3]));
    }
    return ret;
}
std_ReturnType sev_seg_write_number(const sev_seg_t *seg,uint8 number){
    std_ReturnType ret = E_OK;
    if(seg == NULL || number > 9){
        ret = E_NOT_OK;
    }
    else{
        
        gpio_pin_write_logic(&(seg->pins[0]),(number & 0x01));
        gpio_pin_write_logic(&(seg->pins[1]),((number >> 1) & 0x01));
        gpio_pin_write_logic(&(seg->pins[2]),((number >> 2) & 0x01));
        gpio_pin_write_logic(&(seg->pins[3]),((number >> 3) & 0x01));
        
    }
    return ret;
}
