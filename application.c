 /* 
 * File:   application.c
 * Author: MOHAMED TAREK
 *
 * Created on April 22, 2024, 5:31 AM
 */


#include "application.h"
std_ReturnType ret = E_NOT_OK;
void isr(void){
    led_turn_toggle(&led1);
}
volatile uint8 chara;
usart_t esuart = {.baudrate = 9600,.mode = BAUDRATE_ASYN_8BIT_HIGH_SPEED,.tx.TX_enable = TX_ENABLE,.tx.tx_9bit_enable = ESUART_8BIT,.rx.RX_enable = 1,.rx.rx_9bit_enable = ESUART_8BIT};
int main() {
    application_initialize();
    ESUART_ASYNC_INIT(&esuart);
    while(1){
        
        
        ESUART_ASYNC_READ_BYTE_BLOCKING(&chara);
        ESUART_ASYNC_WRITE_BYTE_BLOCKING(chara);
        __delay_ms(200);
        ESUART_ASYNC_WRITE_BYTE_BLOCKING('*');
    }
    return (EXIT_SUCCESS);
}
void application_initialize(){
    ret = Ecu_initialize();
}
