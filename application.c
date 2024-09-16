 /* 
 * File:   application.c
 * Author: MOHAMED TAREK
 *
 * Created on April 22, 2024, 5:31 AM
 */


#include "application.h"
std_ReturnType ret = E_NOT_OK;
pin_config_t pin = {.port = PORTD_INDEX, .pin = PIN0, .direction = GPIO_DIRECTION_OUTPUT,.logic = GPIO_LOW};
int main() {
    spi_t spi = {.idle_state = SPI_HIGH_IDLE,.sample = SPI_SAMPLE_AT_THE_END,.transmit_logic = SPI_TRANSMIT_LOW_ACTIVE,.mode = MASTER_FOSC_DIV_4};
    
    application_initialize();
    gpio_pin_initialize(&pin);
    SPI_INIT(&spi);
    while(1){
     SPI_TRANSMIT_DATA(&spi,0x69);
     __delay_ms(1000);
    }
    return (EXIT_SUCCESS);
}
void application_initialize(){
    ret = Ecu_initialize();
}
