/* 
 * File:   application.c
 * Author: MOHAMED TAREK
 *
 * Created on April 22, 2024, 5:31 AM
 */


#include "application.h"

std_ReturnType ret = E_NOT_OK;
uint8 value = ZERO_INIT ;
int main() {
    application_initialize();
    lcd_8bit_send_string_pos(&lcd1,3,5,"Teko");
    lcd_4bit_send_string_pos(&lcd2,2,15,"TEKOOOO");
    
        
    while(1){
    }
    return (EXIT_SUCCESS);
}
void application_initialize(){
    ret = Ecu_initialize();
}
