/* 
 * File:   hal_spi.c
 * Author: Mohamed Tarek
 *
 * Created on September 16, 2024, 2:37 AM
 */
#include "hal_spi.h"

#if MSSP_INTERRUPT_ENABLED
void (*DefaultHandler)(void);
#endif
static void spi_sample_select(const spi_t *spi);
static void spi_idle_state(const spi_t *spi);
static void spi_transimt_logic(const spi_t *spi);
static void spi_master_gpio(const spi_t *spi);
static void spi_slave_gpio(const spi_t *spi);
static inline void MSSP_SPI_Interrupt_Configurations(const spi_t *spi);

std_ReturnType SPI_INIT(const spi_t *spi){
    std_ReturnType ret = E_OK;
    if(spi == NULL){
        ret = E_NOT_OK;
    }
    else{
        SPI_DISABLE();
        spi_sample_select(spi);
        spi_idle_state(spi);
        spi_transimt_logic(spi);
        SPI_MODE(spi->mode);
        if((spi->mode == MASTER_FOSC_DIV_4) || (spi->mode == MASTER_FOSC_DIV_16) || (spi->mode == MASTER_FOSC_DIV_64) || (spi->mode == MASTER_TIMER2_DIV_2)){
            spi_master_gpio(spi);
        }
        else if((spi->mode == SLAVE_SS_ENABLE) || (spi->mode == SLAVE_SS_DISABLED)){
            spi_slave_gpio(spi);
        }
        else{/* Nothing */}
        MSSP_SPI_Interrupt_Configurations(spi);
        SPI_ENABLE();
    }
    return ret;
}
std_ReturnType SPI_DEINIT(const spi_t *spi){
    std_ReturnType ret = E_OK;
    if(spi == NULL){
        ret = E_NOT_OK;
    }
    else{
        SPI_DISABLE();
    }
    return ret;
}
std_ReturnType SPI_TRANSMIT_DATA(const spi_t *spi,uint8 data){
    std_ReturnType ret = E_OK;
    if(spi == NULL){
        ret = E_NOT_OK;
    }
    else{
        SSPBUF = (uint8)data;
        while(!(PIR1bits.SSPIF));
        MSSP_CLEAR_FLAG();
    }
    return ret;
}
std_ReturnType SPI_READ_DATA(const spi_t *spi,uint8 *data){
    std_ReturnType ret = E_OK;
    if(spi == NULL){
        ret = E_NOT_OK;
    }
    else{
        while(!SSPSTATbits.BF);
        *data = SSPBUF;
    }
    return ret;
}

static void spi_sample_select(const spi_t *spi){
    if(spi->sample == SPI_SAMPLE_AT_THE_END){
        SPI_SAMPLE_END();
    }
    else if(spi->sample == SPI_SAMPLE_AT_THE_MIDDLE){
        SPI_SAMPLE_MIDLLE();
    }
    else{/* Nothing */}
}

static void spi_idle_state(const spi_t *spi){
    if(spi->idle_state == SPI_HIGH_IDLE){
        SPI_IDLE_HIGH();
    }
    else if(spi->idle_state == SPI_LOW_IDLE){
        SPI_IDLE_LOW();
    }
    else{/* Nothing */}
}

static void spi_transimt_logic(const spi_t *spi){
    if(spi->transmit_logic == SPI_TRANSMIT_ACTIVE_LOW){
        SPI_TRANSIMIT_ACTIVE_TO_LOW();
    }
    else if(spi->transmit_logic == SPI_TRANSMIT_LOW_ACTIVE){
        SPI_TRANSIMIT_LOW_TO_ACTIVE();
    }
    else{/* Nothing */}
}

static void spi_master_gpio(const spi_t *spi){
    pin_config_t SPI_SDO = {.port = PORTC_INDEX, .pin = PIN5, .direction = GPIO_DIRECTION_OUTPUT};
    pin_config_t SPI_SDI = {.port = PORTC_INDEX, .pin = PIN4, .direction = GPIO_DIRECTION_INPUT};
    pin_config_t SPI_CLK = {.port = PORTC_INDEX, .pin = PIN3, .direction = GPIO_DIRECTION_OUTPUT};
    
     gpio_pin_direction_intialize(&SPI_SDO); 
     gpio_pin_direction_intialize(&SPI_SDI);
    gpio_pin_direction_intialize(&SPI_CLK);
}

static void spi_slave_gpio(const spi_t *spi){
    pin_config_t SPI_SDO = {.port = PORTC_INDEX, .pin = PIN5, .direction = GPIO_DIRECTION_OUTPUT};
    pin_config_t SPI_SDI = {.port = PORTC_INDEX, .pin = PIN4, .direction = GPIO_DIRECTION_INPUT};
    pin_config_t SPI_CLK = {.port = PORTC_INDEX, .pin = PIN3, .direction = GPIO_DIRECTION_INPUT};
    pin_config_t SPI_SS = {.port = PORTA_INDEX, .pin = PIN5, .direction = GPIO_DIRECTION_INPUT};
    gpio_pin_direction_intialize(&SPI_SDO); 
    gpio_pin_direction_intialize(&SPI_SDI);
    gpio_pin_direction_intialize(&SPI_CLK);
    if(SLAVE_SS_ENABLE == spi->mode){
        gpio_pin_direction_intialize(&SPI_SS);
    }
}

static inline void MSSP_SPI_Interrupt_Configurations(const spi_t *spi){
    
    DefaultHandler = spi->SPI_DefaultInterruptHandler;
    
#if INETRRUPT_PRIORITY
#if MSSP_INTERRUPT_ENABLED
    INTERRUPT_PRIORITY_ENABLED();
    MSSP_CLEAR_FLAG();
    MSSP_INTERRUPT_BUS_COLLISION_CLEAR_FLAG();
    if(spi->mssp_spi_priority == HIGH_PRIORITY){
        INTERRUPT_HIGH_PRIORITY_INTERRUPT_ENABLED();
        MSSP_HIGH_PRIORITY();
    }
    else if(spi->mssp_spi_priority == LOW_PRIORITY){
        INTERRUPT_LOW_PRIORITY_INTERRUPT_ENABLED();
        MSSP_LOW_PRIORITY();
    }
#endif
#elif MSSP_INTERRUPT_ENABLED
    INTERRUPT_GLOBAL_INTERRUPT_ENABLED();
    INTERRUPT_PERIPHERAL_ENABLED();
    MSSP_INTERRUPT_ENABLE();
    MSSP_CLEAR_FLAG();
#endif
}

void MSSP_SPI_ISR(void){
#if MSSP_INTERRUPT_ENABLED
    MSSP_CLEAR_FLAG();
    if(DefaultHandler){
        DefaultHandler();
    }
#endif
}