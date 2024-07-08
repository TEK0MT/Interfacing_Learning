 /* 
 * File:   application.c
 * Author: MOHAMED TAREK
 *
 * Created on April 22, 2024, 5:31 AM
 */


#include "application.h"

std_ReturnType ret = E_NOT_OK;

int main() {

    application_initialize();
    //uint8 text[7];
    //uint8 value = 210;
    //convert_uint8_to_string(value,text);
    
    
    while(1){
        /*lcd_8bit_custom_character(&lcd1,1,20,customChar,0);
        lcd_8bit_custom_character(&lcd1,1,20,customChar2,0);
        lcd_8bit_custom_character(&lcd1,1,20,customChar3,0);
        lcd_8bit_custom_character(&lcd1,1,20,customChar4,0);
        lcd_8bit_custom_character(&lcd1,1,20,customChar5,0);
        lcd_8bit_custom_character(&lcd1,1,20,customChar6,0);*/
        lcd_8bit_send_string_pos(&lcd1,1,15,"3OKSHA");
        lcd_8bit_custom_character(&lcd1,2,15,customChar7,1);
        
        //counter++;
        
    }
    return (EXIT_SUCCESS);
}
void application_initialize(){
    ret = Ecu_initialize();
}
