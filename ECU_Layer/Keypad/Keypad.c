/* 
 * File:   Keypad.c
 * Author: Mohamed Tarek
 *
 * Created on July 2, 2024, 2:09 AM
 */
#include "Keypad.h"

uint8 keypad_values[KEYPAD_ROWS][KEYPAD_COLOUMNS] = {
                                                    {'7','8','9','/'},
                                                    {'4','5','6','*'},
                                                    {'1','2','3','-'},
                                                    {'#','0','=','+'}
    
                                                    };





/**
 * 
 * @param _keypad_obj
 * @return std return type variable
 */
std_ReturnType keypad_initialize(const keypad_t *_keypad_obj){
    std_ReturnType ret = E_OK;
    uint8 row_counter = ZERO_INIT,coloumns_conter = ZERO_INIT;
    if(_keypad_obj == NULL){
        ret = E_NOT_OK;
    }
    else{
        for(row_counter = ZERO_INIT;row_counter < KEYPAD_ROWS;row_counter++){
            ret = gpio_pin_initialize(&(_keypad_obj->rows[row_counter]));
        }
        for(coloumns_conter = ZERO_INIT;row_counter < KEYPAD_COLOUMNS;coloumns_conter++){
            ret = gpio_pin_initialize(&(_keypad_obj->coloumns[coloumns_conter]));
        }
    }
    return ret;
}

/**
 * 
 * @param _keypad_obj
 * @param value
 * @return 
 */
std_ReturnType keypad_read_value(const keypad_t *_keypad_obj, uint8 *value) {
    std_ReturnType ret = E_OK;
    uint8 row_counter = ZERO_INIT, coloumns_conter = ZERO_INIT, l_counter = ZERO_INIT;
    uint8 value_l = 0;
    if (_keypad_obj == NULL || value == NULL) {
        ret = E_NOT_OK;
    } else {
        for (row_counter = ZERO_INIT; row_counter < KEYPAD_ROWS; row_counter++) {
            for (l_counter = ZERO_INIT; l_counter < KEYPAD_ROWS; l_counter++) {
                ret = gpio_pin_write_logic(&(_keypad_obj->rows[l_counter]), GPIO_LOW);
            }
            ret = gpio_pin_write_logic(&(_keypad_obj->rows[row_counter]), GPIO_HIGH);
            __delay_ms(10);

            for (coloumns_conter = ZERO_INIT; coloumns_conter < KEYPAD_COLOUMNS; coloumns_conter++) {
                ret = gpio_pin_read_logic(&(_keypad_obj->coloumns[coloumns_conter]), &value_l);
                if (value_l == GPIO_HIGH) {
                    *value = keypad_values[row_counter][coloumns_conter];
                }
            }
        }
        return ret;
    }
}