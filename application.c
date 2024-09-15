 /* 
 * File:   application.c
 * Author: MOHAMED TAREK
 *
 * Created on April 22, 2024, 5:31 AM
 */


#include "application.h"
std_ReturnType ret = E_NOT_OK;
volatile uint32 slave2 = 0;
volatile uint32 slave1 = 0;
#define SLAVE1 0x60
#define SLAVE2 0x62
void isr(void){
    slave1++;
}


volatile uint8 chara;


mmsp_i2c i2c;

uint8 ch = 'A';
uint8 ack = 0;
void send_i2c(mmsp_i2c *i2c,uint8 add,uint8 data){
    MSSP_I2C_SEND_START(i2c);
    MSSP_I2C_MASTER_WRITE_BLOCKING(i2c,add,&ack);
    __delay_ms(50);
    MSSP_I2C_MASTER_WRITE_BLOCKING(i2c,data,&ack);
    __delay_ms(50);
    MSSP_I2C_SEND_STOP(i2c);
}

int main() {
    
    i2c.i2c_clock = 100000;
    i2c.cfg.mode = MASTER_MODE_SELECT;
    i2c.cfg.i2c_mode_cfg = MASTER_MODE;
    i2c.cfg.slave_address = SLAVE1;
    i2c.cfg.slew_rate = SLEW_RATE_DISABLED;
    i2c.cfg.smbus = SMBUS_DISABLED;
   i2c.I2C_DefaultInterruptHandler = isr;
    
    application_initialize();
    MSSP_I2C_INIT(&i2c);
    while(1){
        
      
      send_i2c(&i2c,SLAVE1,'A');
      __delay_ms(400);
      send_i2c(&i2c,SLAVE2,'B');
      __delay_ms(400);
      send_i2c(&i2c,SLAVE1,'C');
      __delay_ms(400);
      send_i2c(&i2c,SLAVE2,'D');
      __delay_ms(400);
      // __delay_ms(1000);
    }
    return (EXIT_SUCCESS);
}
void application_initialize(){
    ret = Ecu_initialize();
}
