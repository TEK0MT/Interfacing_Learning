/* 
 * File:   mcal_external_interrupt.h
 * Author: Mohamed Tarek
 *
 * Created on July 13, 2024, 8:50 AM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H
/*Section : includes */
#include "mcal_interrupt_config.h"
/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */
#if EXTERNAL_INETRRUPT
#define INTERRUPT_EXTERNAL_INT0_ENBABLE()            (INTCONbits.INT0IE = 1)
#define INTERRUPT_EXTERNAL_INT0_DISABLE()            (INTCONbits.INT0IE = 0)

#define INTERRUPT_EXTERNAL_INT0_CLEAR_FLAG()         (INTCONbits.INT0IF = 0)
#define INTERRUPT_EXTERNAL_INT0_RISING_EDGE()        (INTCON2bits.INTEDG0 = 1)
#define INTERRUPT_EXTERNAL_INT0_FALLING_EDGE()       (INTCON2bits.INTEDG0 = 0)


#define INTERRUPT_EXTERNAL_INT1_ENBABLE()           (INTCON3bits.INT1IE = 1)
#define INTERRUPT_EXTERNAL_INT1_DISABLE()           (INTCON3bits.INT1IE = 0)

#define INTERRUPT_EXTERNAL_INT1_CLEAR_FLAG()         (INTCON3bits.INT1IF = 0)
#define INTERRUPT_EXTERNAL_INT1_RISING_EDGE()        (INTCON2bits.INTEDG1 = 1)
#define INTERRUPT_EXTERNAL_INT1_FALLING_EDGE()       (INTCON2bits.INTEDG1 = 0)



#define INTERRUPT_EXTERNAL_INT2_ENBABLE()            (INTCON3bits.INT2IE = 1)
#define INTERRUPT_EXTERNAL_INT2_DISABLE()            (INTCON3bits.INT2IE = 0)

#define INTERRUPT_EXTERNAL_INT2_CLEAR_FLAG()         (INTCON3bits.INT2IF = 0)
#define INTERRUPT_EXTERNAL_INT2_RISING_EDGE()        (INTCON2bits.INTEDG2 = 1)
#define INTERRUPT_EXTERNAL_INT2_FALLING_EDGE()       (INTCON2bits.INTEDG2 = 0)

#if EXTERNAL_ONCHANGE_INETRRUPT
#define ONCHANGE_INTERRUPT_ENABLE()                  (INTCONbits.RBIE = 1)
#define ONCHANGE_INTERRUPT_DISABLE()                 (INTCONbits.RBIE = 0)

#define ONCHANGE_INTERRUPT_CLEAR_FLAG()              (INTCONbits.RBIF = 0)
#endif


#if INETRRUPT_PRIORITY
#define INTERRUPT_EXTERNAL_INT1_HIGH_PRIORITY()      (INTCON3bits.INT1IP = 1)
#define INTERRUPT_EXTERNAL_INT1_LOW_PRIORITY()       (INTCON3bits.INT1IP = 0)

#define INTERRUPT_EXTERNAL_INT2_HIGH_PRIORITY()      (INTCON3bits.INT2IP = 1)
#define INTERRUPT_EXTERNAL_INT2_LOW_PRIORITY()       (INTCON3bits.INT2IP = 0)

#define ONCHANGE_INTERRUPT_HIGH_PRIORITY()           (INTCON2bits.RBIP = 1)
#define ONCHANGE_INTERRUPT_LOW_PRIORITY()           (INTCON2bits.RBIP = 0)
#endif

#endif

/* Section : Data Type Declarations */
typedef enum{
    INTX0 = 0,
    INTX1,
    INTX2
}intx_src;

typedef enum{
    Falling_Edge = 0,
    Rising_Edge 
}intx_edge;

typedef struct{
    void (*EXT_INTERRUPT_HANDLER)(void);
    pin_config_t pin;
    intx_src intx;
    intx_edge edge;
    intx_priority priority;
}interrupt_Intx_t;

typedef struct{
    void (*EXT_INTERRUPT_HANDLER_HIGH)(void);
    void (*EXT_INTERRUPT_HANDLER_LOW)(void);
    pin_config_t pin;
    intx_priority priority;
}interrupt_Rbx_t;
/* Section : Function Declarations */
std_ReturnType Interrupt_INTx_Init(const interrupt_Intx_t *int_obj);
std_ReturnType Interrupt_INTx_DeInit(const interrupt_Intx_t *int_obj);

std_ReturnType Interrupt_RBx_Init(const interrupt_Rbx_t *int_obj);
std_ReturnType Interrupt_RBx_DeInit(const interrupt_Rbx_t *int_obj);
#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

