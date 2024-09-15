/* 
 * File:   hal_i2c.h
 * Author: Mohamed Tarek
 *
 * Created on September 11, 2024, 8:44 AM
 */

#ifndef HAL_I2C_H
#define	HAL_I2C_H
/*Section : includes */
#include "pic18f4620.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../GPIO/hal_gpio.h"

/* Section : Macro Declarations */
#define  MASTER_MODE        0x08
#define SLAVE_7_BIT_ADDRESS 0x06
#define SLAVE_10_BIT_ADDRESS 0x07
#define SLAVE_7_BIT_ADDRESS_STOP_STARET_INTERRUPT_ENABLED 0x0A
#define SLAVE_10_BIT_ADDRESS_STOP_STARET_INTERRUPT_ENABLED 0x0A

#define MASTER_MODE_SELECT      0x00
#define SLAVE_MODE_SELECT      0x01

#define SMBUS_ENABLED       0x01
#define SMBUS_DISABLED       0x00

#define SLEW_RATE_ENABLED   0x01
#define SLEW_RATE_DISABLED   0x00

#define START_STOP_DETECTED 0x01

#define ENABLE_RECIEVE 0x01

#define GENERAL_CALL_ENABLE 0x01
#define GENERAL_CALL_DISABLE 0x00

#define ACKNOWLEDGE_RECEIVED_FROM_SLAVE  0x00
#define ACKNOWLEDGE_NOT_RECEIVED_FROM_SLAVE  0x01

#define I2C_MASTER_SEND_ACK  0
#define I2C_MASTER_SEND_NACK 1
/* Section : Macro Functions Declarations */
#define MSSP_I2C_ENABLE()   (SSPCON1bits.SSPEN = 1)
#define MSSP_I2C_DISABLE()   (SSPCON1bits.SSPEN = 0)

#define SLEW_RATE_CONTROL_ENABLE()     (SSPSTATbits.SMP = 1)
#define SLEW_RATE_CONTROL_DISABLE()     (SSPSTATbits.SMP = 1)

#define SMBUS_CONTROL_ENABLE()     (SSPSTATbits.CKE = 1)
#define SMBUS_CONTROL_DISABLE()     (SSPSTATbits.CKE = 1)

#define SLAVE_RELEASE_CLOCK()       (SSPCON1bits.CKP = 1)
#define SLAVE_HOLDS_CLOCK()       (SSPCON1bits.CKP = 0)

#define I2C_MODE_SELECT(mode)       (SSPCON1bits.SSPM = mode)

#define MASTER_RECIEVE_ENABLE()   (SSPCON2bits.RCEN = 1)
#define MASTER_RECIEVE_DISABLE()   (SSPCON2bits.RCEN = 0)

/* Section : Data Type Declarations */
typedef struct{
    uint8 i2c_mode_cfg;
    uint8 slave_address;
    uint8 mode      :1;
    uint8 slew_rate     :1;
    uint8 smbus     :1;
    uint8 general_call  :1;
    uint8 master_recieve_mode :1;
    uint8 reserved :3;
 
}i2c_cfg;

typedef struct{
    i2c_cfg cfg;
#if MSSP_INTERRUPT_ENABLED
    void (*I2C_Report_Write_Collision)(void);	/* Write Collision Indicator */
    void (*I2C_DefaultInterruptHandler)(void); 	/* Default Interrupt Handler */
    void (*I2C_Report_Receive_Overflow)(void); 	/* Receive Overflow Indicator */
#if INETRRUPT_PRIORITY
    interrupt_priority mssp_i2c_priority;
    interrupt_priority mssp_i2c_bc_priority;
#endif  
#endif    
    uint32 i2c_clock;
}mmsp_i2c;
/* Section : Function Declarations */
std_ReturnType MSSP_I2C_INIT(const mmsp_i2c *i2c);
std_ReturnType MSSP_I2C_DEINIT(const mmsp_i2c *i2c);
std_ReturnType MSSP_I2C_SEND_START(const mmsp_i2c *i2c);
std_ReturnType MSSP_I2C_SEND_REPEATED_START(const mmsp_i2c *i2c);
std_ReturnType MSSP_I2C_SEND_STOP(const mmsp_i2c *i2c);
std_ReturnType MSSP_I2C_MASTER_WRITE_BLOCKING(const mmsp_i2c *i2c,uint8 data,uint8 *ack);
std_ReturnType MSSP_I2C_MASTER_READ_BLOCKING(const mmsp_i2c *i2c,uint8 *data,uint8 *ack);
#endif	/* HAL_I2C_H */

