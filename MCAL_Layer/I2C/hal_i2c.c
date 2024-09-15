/* 
 * File:   hal_i2c.c
 * Author: Mohamed Tarek
 *
 * Created on September 11, 2024, 8:44 AM
 */
#include "hal_i2c.h"

static inline void MSSP_I2C_Interrupt_Configurations(const mmsp_i2c *i2c);
#if MSSP_INTERRUPT_ENABLED
static void (*I2C_Report_Write_Collision_InterruptHandler)(void) = NULL;
static void (*I2C_DefaultInterruptHandle)(void) = NULL;
static void (*I2C_Report_Receive_Overflow_InterruptHandle)(void) = NULL;
#endif

std_ReturnType MSSP_I2C_INIT(const mmsp_i2c *i2c){
    std_ReturnType ret = E_OK;
    if(i2c == NULL){
        ret = E_NOT_OK;
    }
    else{
        MSSP_I2C_DISABLE();
        if(i2c->cfg.mode == MASTER_MODE_SELECT){
            I2C_MODE_SELECT(MASTER_MODE);
            if(i2c->cfg.master_recieve_mode == ENABLE_RECIEVE){
                
                
            }
            else{
                MASTER_RECIEVE_DISABLE();
            }
            SSPADD = (uint8)((((i2c->i2c_clock) * 4) / _XTAL_FREQ) - 1);
        }
        else if(i2c->cfg.mode == SLAVE_MODE_SELECT){
            if(i2c->cfg.general_call == GENERAL_CALL_ENABLE){
                SSPCON2bits.GCEN = 1;
            }
            else if(i2c->cfg.general_call == GENERAL_CALL_DISABLE){
                SSPCON2bits.GCEN = 0;
            }
            else{/*Nothing*/}
            SSPCON1bits.WCOL = 0;
            SSPCON1bits.SSPOV = 0;
            SSPADD = i2c->cfg.slave_address;
            SLAVE_RELEASE_CLOCK();
            I2C_MODE_SELECT(i2c->cfg.i2c_mode_cfg);
        }
        else{/*Nothing*/}
        if(i2c->cfg.slew_rate == SLEW_RATE_ENABLED){
            SLEW_RATE_CONTROL_ENABLE();
        }
        else if(i2c->cfg.slew_rate == SLEW_RATE_DISABLED){
            SLEW_RATE_CONTROL_DISABLE();
        }
        else{/*Nothing*/}
        if(i2c->cfg.smbus == SMBUS_ENABLED){
            SMBUS_CONTROL_ENABLE();
        }
        if(i2c->cfg.smbus == SMBUS_DISABLED){
            SMBUS_CONTROL_DISABLE();
        }
        else{/*Nothing*/}
        MSSP_I2C_Interrupt_Configurations(i2c);
        TRISCbits.RC3 = 1;
        TRISCbits.RC4 = 1;
        MSSP_I2C_ENABLE();
    }
    return ret;
}
std_ReturnType MSSP_I2C_DEINIT(const mmsp_i2c *i2c){
    std_ReturnType ret = E_OK;
    if(i2c == NULL){
        ret = E_NOT_OK;
    }
    else{
        MSSP_I2C_DISABLE();
    }
    return ret;
}
std_ReturnType MSSP_I2C_SEND_START(const mmsp_i2c *i2c){
    std_ReturnType ret = E_OK;
    if(i2c == NULL){
        ret = E_NOT_OK;
    }
    else{
        SSPCON2bits.SEN = 1;
        while(SSPCON2bits.SEN);
        MSSP_CLEAR_FLAG();
        if(SSPSTATbits.S){
            ret = E_OK;
        }
        else{
            ret = E_NOT_OK;
        }
    }
    return ret;
}
std_ReturnType MSSP_I2C_SEND_REPEATED_START(const mmsp_i2c *i2c){
    std_ReturnType ret = E_OK;
    if(i2c == NULL){
        ret = E_NOT_OK;
    }
    else{
        SSPCON2bits.RSEN = 1;
        while(SSPCON2bits.RSEN);
        MSSP_CLEAR_FLAG();
       
    }
    return ret;
}
std_ReturnType MSSP_I2C_SEND_STOP(const mmsp_i2c *i2c){
    std_ReturnType ret = E_OK;
    if(i2c == NULL){
        ret = E_NOT_OK;
    }
    else{
        SSPCON2bits.PEN = 1;
        while(SSPCON2bits.PEN);
        MSSP_CLEAR_FLAG();
        if(SSPSTATbits.P){
            ret = E_OK;
        }
        else{
            ret = E_NOT_OK;
        }
    }
    return ret;
}
std_ReturnType MSSP_I2C_MASTER_WRITE_BLOCKING(const mmsp_i2c *i2c,uint8 data,uint8 *ack){
    std_ReturnType ret = E_OK;
    if(i2c == NULL){
        ret = E_NOT_OK;
    }
    else{
        SSPBUF = data;
        while(SSPSTATbits.BF);
        MSSP_CLEAR_FLAG();
        if(SSPCON2bits.ACKSTAT == ACKNOWLEDGE_RECEIVED_FROM_SLAVE){
            *ack = ACKNOWLEDGE_RECEIVED_FROM_SLAVE;
        }
        else{
            *ack = ACKNOWLEDGE_NOT_RECEIVED_FROM_SLAVE;
        }
    }
    return ret;
}
std_ReturnType MSSP_I2C_MASTER_READ_BLOCKING(const mmsp_i2c *i2c,uint8 *data,uint8 *ack){
    std_ReturnType ret = E_OK;
    if(i2c == NULL){
        ret = E_NOT_OK;
    }
    else{
        MASTER_RECIEVE_ENABLE();
        while(SSPSTATbits.BF);
        *data = SSPBUF;
        MSSP_CLEAR_FLAG();
        if(I2C_MASTER_SEND_ACK == ack){
            SSPCON2bits.ACKDT = 0; /* Acknowledge */
            /* Initiates Acknowledge sequence on SDA and SCL pins and transmit ACKDT data bit. */
            SSPCON2bits.ACKEN = 1; 
            while(SSPCON2bits.ACKEN); /* Automatically cleared by hardware */
        }
        else if(I2C_MASTER_SEND_NACK == ack){
            SSPCON2bits.ACKDT = 1; /* Not Acknowledge */
            /* Initiates Acknowledge sequence on SDA and SCL pins and transmit ACKDT data bit. */
            SSPCON2bits.ACKEN = 1;
            while(SSPCON2bits.ACKEN); /* Automatically cleared by hardware */
        }
        else { /* Nothing */ }
        
    }
    return ret;
}

void MSSP_I2C_ISR(void){
#if MSSP_INTERRUPT_ENABLED    
    MSSP_CLEAR_FLAG();
    if(I2C_DefaultInterruptHandle){
        I2C_DefaultInterruptHandle();
    }
#endif
}

void MSSP_I2C_BC_ISR(void){
#if MSSP_INTERRUPT_ENABLED
    MSSP_INTERRUPT_BUS_COLLISION_CLEAR_FLAG();
    if(I2C_Report_Write_Collision_InterruptHandler){
        I2C_Report_Write_Collision_InterruptHandler();
    }
#endif
}

static inline void MSSP_I2C_Interrupt_Configurations(const mmsp_i2c *i2c){
    I2C_Report_Write_Collision_InterruptHandler = i2c->I2C_Report_Write_Collision;
    I2C_DefaultInterruptHandle = i2c->I2C_DefaultInterruptHandler;
    I2C_Report_Receive_Overflow_InterruptHandle = i2c->I2C_Report_Receive_Overflow;
#if INETRRUPT_PRIORITY
#if MSSP_INTERRUPT_ENABLED
    INTERRUPT_PRIORITY_ENABLED();
    MSSP_CLEAR_FLAG();
    MSSP_INTERRUPT_BUS_COLLISION_CLEAR_FLAG();
    if(i2c->mssp_i2c_priority == HIGH_PRIORITY){
        INTERRUPT_HIGH_PRIORITY_INTERRUPT_ENABLED();
        MSSP_HIGH_PRIORITY();
    }
    else if(i2c->mssp_i2c_priority == LOW_PRIORITY){
        INTERRUPT_LOW_PRIORITY_INTERRUPT_ENABLED();
        MSSP_LOW_PRIORITY();
    }
    if(i2c->mssp_i2c_bc_priority == HIGH_PRIORITY){
        INTERRUPT_HIGH_PRIORITY_INTERRUPT_ENABLED();
        MSSP_HIGH_BUS_COLLISION_PRIORITY();
    }
    else if(i2c->mssp_i2c_bc_priority == LOW_PRIORITY){
        INTERRUPT_LOW_PRIORITY_INTERRUPT_ENABLED();
        MSSP_LOW_BUS_COLLISION_PRIORITY();
    }
#endif
#elif MSSP_INTERRUPT_ENABLED
    INTERRUPT_GLOBAL_INTERRUPT_ENABLED();
    INTERRUPT_PERIPHERAL_ENABLED();
    MSSP_INTERRUPT_ENABLE();
    MSSP_CLEAR_FLAG();
    MSSP_INTERRUPT_BUS_COLLISION_CLEAR_FLAG();
#endif
        
   
}
