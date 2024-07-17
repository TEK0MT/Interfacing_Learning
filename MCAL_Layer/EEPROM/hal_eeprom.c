/* 
 * File:   hal_eeprom.c
 * Author: Mohamed Tarek
 *
 * Created on July 17, 2024, 5:32 AM
 */
#include "hal_eeprom.h"
std_ReturnType WRITE_DATA_EEPROM(uint16 add,uint8 data){
    std_ReturnType ret = E_OK;
    uint8 status = INTCONbits.GIEH;

        
        EEADRH = (uint8)((add >> 8) & 0x03);
        EEADR = (uint8)(add & 0xFF);
        EEDATA = data;
        EECON1bits.EEPGD = ACCESS_EEPROM_DATA;
        EECON1bits.CFGS = ACCESS_FLASH_EEPROM_DATA;
        EECON1bits.WREN = ALLOW_WRITE_CYCLE;
        INTERRUPT_GLOBAL_INTERRUPT_DISABLED();
        EECON2 = 0x55;
        EECON2 = 0xAA;
        EECON1bits.WR = WRITE_ON_EEPROM;
        while(EECON1bits.WR);
        EECON1bits.WREN = INHIBIT_WRITE_CYCLE;
        INTCONbits.GIEH = status;
    return ret;
}
std_ReturnType READ_DATA_EEPROM(uint16 add,uint8 *data){
    std_ReturnType ret = E_OK;
    uint8 status = INTCONbits.GIEH;
    
        
        EEADRH = (uint8)((add >> 8) & 0x03);
        EEADR = (uint8)(add & 0xFF);
        EECON1bits.EEPGD = ACCESS_EEPROM_DATA;
        EECON1bits.CFGS = ACCESS_FLASH_EEPROM_DATA;
        EECON1bits.RD = READ_OFF_EEPROM;
        NOP();
        NOP();
        *data = EEDATA;
    return ret;
}