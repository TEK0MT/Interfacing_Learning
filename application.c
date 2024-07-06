 /* 
 * File:   application.c
 * Author: MOHAMED TAREK
 *
 * Created on April 22, 2024, 5:31 AM
 */


#include "application.h"

std_ReturnType ret = E_NOT_OK;
    uint8 customChar[] = {
  0x0E,
  0x0A,
  0x1B,
  0x11,
  0x11,
  0x11,
  0x1F,
  0x00
};
int main() {

    application_initialize();
        
        //lcd_8bit_custom_character(&lcd3,1,10,customChar,1);
    lcd_8bit_send_string(&lcd1,"kk");
    while(1){
        
        
        //counter++;
        
    }
    return (EXIT_SUCCESS);
}
void application_initialize(){
    ret = Ecu_initialize();
}
