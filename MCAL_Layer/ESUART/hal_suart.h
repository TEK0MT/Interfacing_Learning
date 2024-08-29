/* 
 * File:   hal_suart.h
 * Author: Mohamed Tarek
 *
 * Created on August 28, 2024, 9:50 AM
 */

#ifndef HAL_ESUART_H
#define	HAL_ESUART_H
/*Section : includes */
#include "../GPIO/hal_gpio.h"
#include "pic18f4620.h"
#include "../Interrupt/mcal_internal_interrupt.h"
/* Section : Macro Declarations */
#define ASYNCRONOUS_MODE 0
#define SYNCRONOUS_MODE 1

#define ASYNCRONOUS_HIGH_SPEED 1
#define ASYNCRONOUS_LOW_SPEED 0


#define BAUD_RATE_16BIT 1
#define BAUD_RATE_8BIT 0

#define ASYNCRONOUS_HIGH_SPEED      1
#define ASYNCRONOUS_LOW_SPEED      0

#define ESUART_9BIT                 1
#define ESUART_8BIT                 0

#define TX_ENABLE                   1
#define TX_DISABLE                   0

#define RX_ENABLE                   1
#define RX_DISABLE                   0

/* Section : Macro Functions Declarations */
#define TX_ENABLE_MODE()        (TXSTAbits.TXEN = 1)
#define TX_DISABLE_MODE()        (TXSTAbits.TXEN = 0)

#define RX_ENABLE_MODE()        (RCSTAbits.CREN = 1)
#define RX_DISABLE_MODE()        (RCSTAbits.CREN = 0)

#define ASYC_SYC_MODE(mode)    (TXSTAbits.SYNC = mode)

#define TRANSMIT_9BIT_ENABLE(mode)    (TXSTAbits.TX9 = mode)
#define RECIEVE_9BIT_ENABLE(mode)    (RCSTAbits.RX9 = mode)

/* Section : Data Type Declarations */
typedef enum {
    BAUDRATE_ASYN_8BIT_lOW_SPEED,
    BAUDRATE_ASYN_8BIT_HIGH_SPEED,
    BAUDRATE_ASYN_16BIT_lOW_SPEED,
    BAUDRATE_ASYN_16BIT_HIGH_SPEED,
    BAUDRATE_SYN_8BIT,
    BAUDRATE_SYN_16BIT
} baudrate_gen_t;

typedef struct {
    interrupt_priority tx_priority;
    uint8 TX_enable : 1;
    uint8 Interrupt_tx_enable : 1;
    uint8 tx_9bit_enable : 1;
    uint8 reserved : 5;
} usart_tx_cfg;

typedef struct {
    interrupt_priority rx_priority;
    uint8 RX_enable : 1;
    uint8 Interrupt_rx_enable : 1;
    uint8 rx_9bit_enable : 1;
    uint8 reserved : 5;
} usart_rx_cfg;

typedef struct {
    uint32 baudrate;
    baudrate_gen_t mode;
    usart_tx_cfg tx;
    usart_rx_cfg rx;
    void (*EUSART_TxDefaultInterruptHandler)(void);
    void (*EUSART_RxDefaultInterruptHandler)(void);
    void (*EUSART_FramingErrorHandler)(void);
    void (*EUSART_OverrunErrorHandler)(void);
} usart_t;
/* Section : Function Declarations */
std_ReturnType ESUART_ASYNC_INIT(const usart_t *usart);
std_ReturnType ESUART_ASYNC_DEINIT(const usart_t *usart);

std_ReturnType ESUART_ASYNC_WRITE_BYTE_BLOCKING(uint8 data);
std_ReturnType ESUART_ASYNC_WRITE_BYTE_NOBLOCKING(uint8 data);
std_ReturnType EUSART_ASYNC_WriteStringBlocking(uint8 *_data, uint16 str_len);

std_ReturnType ESUART_ASYNC_READ_BYTE_BLOCKING(uint8 *data);
std_ReturnType ESUART_ASYNC_READ_BYTE_NOBLOCKING(uint8 *data);

std_ReturnType EUSART_ASYNC_RX_Restart(void);
#endif	/* HAL_ESUART_H */

