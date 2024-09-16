/* 
 * File:   hal_spi.h
 * Author: Mohamed Tarek
 *
 * Created on September 16, 2024, 2:37 AM
 */

#ifndef HAL_SPI_H
#define	HAL_SPI_H
/*Section : includes */
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "pic18f4620.h"
/* Section : Macro Declarations */
#define SPI_SAMPLE_AT_THE_END 0x01
#define SPI_SAMPLE_AT_THE_MIDDLE 0x00

#define SPI_HIGH_IDLE 0x01
#define SPI_LOW_IDLE 0x00 

#define SPI_TRANSMIT_ACTIVE_LOW 0x01
#define SPI_TRANSMIT_LOW_ACTIVE 0x00
/* Section : Macro Functions Declarations */
#define SPI_ENABLE()    (SSPCON1bits.SSPEN = 1)
#define SPI_DISABLE()    (SSPCON1bits.SSPEN = 0)

#define SPI_IDLE_HIGH()     (SSPCON1bits.CKP = 1)
#define SPI_IDLE_LOW()     (SSPCON1bits.CKP = 0)

#define SPI_TRANSIMIT_ACTIVE_TO_LOW()     (SSPSTATbits.CKE = 1)
#define SPI_TRANSIMIT_LOW_TO_ACTIVE()     (SSPSTATbits.CKE = 0)

#define SPI_SAMPLE_END()    (SSPSTATbits.SMP = 1)
#define SPI_SAMPLE_MIDLLE()    (SSPSTATbits.SMP = 0)

#define SPI_MODE(mode)      (SSPCON1bits.SSPM = mode)
/* Section : Data Type Declarations */
typedef enum{
    MASTER_FOSC_DIV_4,
            MASTER_FOSC_DIV_16,
            MASTER_FOSC_DIV_64,
            MASTER_TIMER2_DIV_2,
            SLAVE_SS_ENABLE,
            SLAVE_SS_DISABLED
}spi_mode;

typedef struct{
    uint8 sample;
    uint8 idle_state;
    uint8 transmit_logic;
    spi_mode mode;
    #if MSSP_INTERRUPT_ENABLED
    void (*SPI_DefaultInterruptHandler)(void); 	/* Default Interrupt Handler */
#if INETRRUPT_PRIORITY
    interrupt_priority mssp_spi_priority;
#endif  
#endif    
}spi_t;
  
/* Section : Function Declarations */
std_ReturnType SPI_INIT(const spi_t *spi);
std_ReturnType SPI_DEINIT(const spi_t *spi);
std_ReturnType SPI_TRANSMIT_DATA(const spi_t *spi,uint8 data);
std_ReturnType SPI_READ_DATA(const spi_t *spi,uint8 *data);

#endif	/* HAL_SPI_H */

