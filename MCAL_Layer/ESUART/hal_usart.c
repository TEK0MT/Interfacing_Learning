/* 
 * File:   hal_suart.c
 * Author: Mohamed Tarek
 *
 * Created on August 28, 2024, 9:50 AM
 */
#include "hal_suart.h"


#if USART_TX_INTERRUPT==INTERRUPT_ENABLED
static void (*EUSART_TxInterruptHandler)(void) = NULL;
#endif
#if USART_RX_INTERRUPT==INTERRUPT_ENABLED
static void (*EUSART_RxInterruptHandler)(void) = NULL;
static void (*EUSART_FramingErrorHandler)(void) = NULL;
static void (*EUSART_OverrunErrorHandler)(void) = NULL;
#endif  




std_ReturnType ESUART_ASYNC_BAUD_RATE(const usart_t *usart);
std_ReturnType ESUART_ASYNC_TX_INIT(const usart_t *usart);
std_ReturnType ESUART_ASYNC_RX_INIT(const usart_t *usart);

std_ReturnType ESUART_ASYNC_INIT(const usart_t *usart) {
    std_ReturnType ret = E_OK;
    if (usart == NULL) {
        ret = E_NOT_OK;
    } else {
        RCSTAbits.SPEN = 0;
        TRISCbits.RC7 = 1;
        TRISCbits.RC6 = 1;
        ESUART_ASYNC_BAUD_RATE(usart);
        ESUART_ASYNC_TX_INIT(usart);
        ESUART_ASYNC_RX_INIT(usart);
        RCSTAbits.SPEN = 1;
    }
    return ret;
}

std_ReturnType ESUART_ASYNC_DEINIT(const usart_t *usart) {
    std_ReturnType ret = E_OK;
    if (usart == NULL) {
        ret = E_NOT_OK;
    } else {
        RCSTAbits.SPEN = 0;
    }
    return ret;
}

std_ReturnType ESUART_ASYNC_WRITE_BYTE_BLOCKING(uint8 data) {
    std_ReturnType ret = E_OK;
    while (!TXSTAbits.TRMT);
#if USART_TX_INTERRUPT == INTERRUPT_ENABLED
    TX_INTERRUPT_ENABLE();
#endif
    TXREG = data;
    return ret;
}

std_ReturnType ESUART_ASYNC_WRITE_BYTE_NOBLOCKING(uint8 data) {
    std_ReturnType ret = E_OK;
    if (TXSTAbits.TRMT) {
        TXREG = data;
    } else {
        ret = E_NOT_OK;
    }
    return ret;
}

std_ReturnType ESUART_ASYNC_READ_BYTE_BLOCKING(uint8 *data) {
    std_ReturnType ret = E_OK;
    if (data == NULL) {
        ret = E_NOT_OK;
    } else {
        while (!PIR1bits.RCIF);

        *data = RCREG;

        return ret;
    }
}

std_ReturnType ESUART_ASYNC_READ_BYTE_NOBLOCKING(uint8 *data) {
    std_ReturnType ret = E_OK;
    if (1 == PIR1bits.RCIF) {
        *data = RCREG;
    } else {
        ret = E_NOT_OK;
    }
    return ret;
}

std_ReturnType EUSART_ASYNC_WriteStringBlocking(uint8 *_data, uint16 str_len) {
    std_ReturnType ret = E_OK;
    uint16 char_counter = ZERO_INIT;
    for (char_counter = ZERO_INIT; char_counter < str_len; char_counter++) {
        ret = ESUART_ASYNC_READ_BYTE_BLOCKING(_data[char_counter]);
    }
    return ret;
}

std_ReturnType EUSART_ASYNC_RX_Restart(void) {
    std_ReturnType ret = E_OK;
    RCSTAbits.CREN = 0;
    RCSTAbits.CREN = 1;
    return ret;
}

std_ReturnType ESUART_ASYNC_BAUD_RATE(const usart_t *usart) {
    float baud_temp = ZERO_INIT;
    std_ReturnType ret = E_OK;
    if (usart == NULL) {
        ret = E_NOT_OK;
    } else {
        switch (usart->mode) {
            case BAUDRATE_ASYN_8BIT_lOW_SPEED:
                ASYC_SYC_MODE(ASYNCRONOUS_MODE);
                TXSTAbits.BRGH = ASYNCRONOUS_LOW_SPEED;
                BAUDCONbits.BRG16 = BAUD_RATE_8BIT;
                baud_temp = ((_XTAL_FREQ / (float) usart->baudrate) / 64) - 1;
                break;

            case BAUDRATE_ASYN_8BIT_HIGH_SPEED:
                ASYC_SYC_MODE(ASYNCRONOUS_MODE);
                TXSTAbits.BRGH = ASYNCRONOUS_HIGH_SPEED;
                BAUDCONbits.BRG16 = BAUD_RATE_8BIT;
                baud_temp = ((_XTAL_FREQ / (float) usart->baudrate) / 16) - 1;
                break;

            case BAUDRATE_ASYN_16BIT_lOW_SPEED:
                ASYC_SYC_MODE(ASYNCRONOUS_MODE);
                TXSTAbits.BRGH = ASYNCRONOUS_LOW_SPEED;
                BAUDCONbits.BRG16 = BAUD_RATE_16BIT;
                baud_temp = ((_XTAL_FREQ / (float) usart->baudrate) / 16) - 1;
                break;

            case BAUDRATE_ASYN_16BIT_HIGH_SPEED:
                ASYC_SYC_MODE(ASYNCRONOUS_MODE);
                TXSTAbits.BRGH = ASYNCRONOUS_HIGH_SPEED;
                BAUDCONbits.BRG16 = BAUD_RATE_16BIT;
                baud_temp = ((_XTAL_FREQ / (float) usart->baudrate) / 4) - 1;
                break;

            case BAUDRATE_SYN_8BIT:
                ASYC_SYC_MODE(SYNCRONOUS_MODE);
                BAUDCONbits.BRG16 = BAUD_RATE_8BIT;
                baud_temp = ((_XTAL_FREQ / (float) usart->baudrate) / 4) - 1;
                break;

            case BAUDRATE_SYN_16BIT:
                ASYC_SYC_MODE(SYNCRONOUS_MODE);
                BAUDCONbits.BRG16 = BAUD_RATE_16BIT;
                baud_temp = ((_XTAL_FREQ / (float) usart->baudrate) / 4) - 1;
                break;

            default:
                ret = E_NOT_OK;

        }
        SPBRG = (uint8) ((uint32) baud_temp);
        SPBRGH = (uint8) ((uint32) baud_temp >> 8);
    }
    return ret;
}

std_ReturnType ESUART_ASYNC_TX_INIT(const usart_t *usart) {
    std_ReturnType ret = E_OK;
    if (usart == NULL) {
        ret = E_NOT_OK;
    } else {
        if (usart->tx.TX_enable == TX_ENABLE) {
            TX_ENABLE_MODE();
            if (usart->tx.tx_9bit_enable == ESUART_9BIT) {
                TRANSMIT_9BIT_ENABLE(ESUART_9BIT);
            } else if (usart->tx.tx_9bit_enable == ESUART_8BIT) {
                TRANSMIT_9BIT_ENABLE(ESUART_8BIT);
            } else {
                /* Nothing */
            }
            if (usart->tx.Interrupt_tx_enable) {
#if USART_TX_INTERRUPT == INTERRUPT_ENABLED
                TX_INTERRUPT_ENABLE();
                EUSART_TxInterruptHandler = usart->EUSART_TxDefaultInterruptHandler;
#if INETRRUPT_PRIORITY
                INTERRUPT_PRIORITY_ENABLED();
                if (usart->tx.tx_priority == HIGH_PRIORITY) {
                    TX_HIGH_PRIORITY();
                } else if (usart->tx.tx_priority == LOW_PRIORITY) {
                    TX_LOW_PRIORITY();
                } else {
                    /* Nothing*/
                }
#else
                INTERRUPT_GLOBAL_INTERRUPT_ENABLED();
                INTERRUPT_PERIPHERAL_ENABLED();
#endif
#endif

            }
        } else if (usart->tx.TX_enable == TX_DISABLE) {
            TX_DISABLE_MODE();
        } else {
        }
    }
}

std_ReturnType ESUART_ASYNC_RX_INIT(const usart_t *usart) {
    std_ReturnType ret = E_OK;
    if (usart == NULL) {
        ret = E_NOT_OK;
    } else {
        if (usart->rx.RX_enable == RX_ENABLE) {
            RX_ENABLE_MODE();
            if (usart->rx.rx_9bit_enable == ESUART_9BIT) {
                RECIEVE_9BIT_ENABLE(ESUART_9BIT);
            } else if (usart->rx.rx_9bit_enable == ESUART_8BIT) {
                RECIEVE_9BIT_ENABLE(ESUART_8BIT);
            } else {
                /* Nothing */
            }
            if (usart->rx.Interrupt_rx_enable) {
#if USART_RX_INTERRUPT == INTERRUPT_ENABLED
                RX_INTERRUPT_ENABLE();
                EUSART_RxInterruptHandler = usart->EUSART_RxDefaultInterruptHandler;
                EUSART_FramingErrorHandler = usart->EUSART_FramingErrorHandler;
                EUSART_OverrunErrorHandler = usart->EUSART_OverrunErrorHandler;
#if INETRRUPT_PRIORITY
                INTERRUPT_PRIORITY_ENABLED();
                if (usart->rx.rx_priority == HIGH_PRIORITY) {
                    RX_HIGH_PRIORITY();
                } else if (usart->rx.rx_priority == LOW_PRIORITY) {
                    RX_LOW_PRIORITY();
                } else {
                    /* Nothing*/
                }
#else
                INTERRUPT_GLOBAL_INTERRUPT_ENABLED();
                INTERRUPT_PERIPHERAL_ENABLED();
#endif
#endif

            }

        } else if (usart->rx.RX_enable == RX_DISABLE) {
            RX_DISABLE_MODE();
        } else {
        }
    }
}

#if USART_TX_INTERRUPT==INTERRUPT_ENABLED

void EUSART_TX_ISR(void) {
    TX_INTERRUPT_DISABLE();
    if (EUSART_TxInterruptHandler) {
        EUSART_TxInterruptHandler();
    } else {
        /* Nothing */
    }
}
#endif


#if USART_RX_INTERRUPT==INTERRUPT_ENABLED

void EUSART_RX_ISR(void) {
    if (EUSART_RxInterruptHandler) {
        EUSART_RxInterruptHandler();
    } else {
        /* Nothing */
    }
    if (EUSART_FramingErrorHandler) {
        EUSART_FramingErrorHandler();
    } else {
        /* Nothing */
    }
    if (EUSART_OverrunErrorHandler) {
        EUSART_OverrunErrorHandler();
    } else {
        /* Nothing */
    }
}
#endif