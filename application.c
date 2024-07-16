 /* 
 * File:   application.c
 * Author: MOHAMED TAREK
 *
 * Created on April 22, 2024, 5:31 AM
 */


#include "application.h"
void int0_isr(void){
    led_turn_toggle(&led1);
    __delay_ms(500);
}
void int1_isr(void){
    led_turn_toggle(&led2);
        __delay_ms(500);

}
void int2_isr(void){
    led_turn_toggle(&led3);
    
        __delay_ms(500);

}
void RB4_isr(void){
    led_turn_toggle(&led1);
    __delay_ms(500);
}
/*interrupt_Intx_t int0 = {.EXT_INTERRUPT_HANDLER = int0_isr,.intx = INTX0,.edge = Rising_Edge,.priority = HIGH_PRIORITY,.pin.port = PORTB_INDEX,.pin.pin = PIN0,.pin.logic = GPIO_DIRECTION_INPUT,.pin.logic = GPIO_LOW};
interrupt_Intx_t int1 = {.EXT_INTERRUPT_HANDLER = int1_isr,.intx = INTX1,.edge = Rising_Edge,.priority = LOW_PRIORITY,.pin.port = PORTB_INDEX,.pin.pin = PIN1,.pin.logic = GPIO_DIRECTION_INPUT,.pin.logic = GPIO_HIGH};
interrupt_Intx_t int2 = {.EXT_INTERRUPT_HANDLER = int2_isr,.intx = INTX2,.edge = Rising_Edge,.priority = HIGH_PRIORITY,.pin.port = PORTB_INDEX,.pin.pin = PIN2,.pin.logic = GPIO_DIRECTION_INPUT,.pin.logic = GPIO_LOW};
*/
interrupt_Rbx_t rb4 = {.EXT_INTERRUPT_HANDLER_HIGH = RB4_isr,.EXT_INTERRUPT_HANDLER_LOW = NULL,.priority = HIGH_PRIORITY,.pin.port = PORTB_INDEX,.pin.pin = PIN4,.pin.logic = GPIO_LOW,.pin.direction = GPIO_DIRECTION_INPUT};
/*interrupt_Rbx_t rb5 = {.EXT_INTERRUPT_HANDLER = int1_isr,.priority = LOW_PRIORITY,.pin.port = PORTB_INDEX,.pin.pin = PIN5,.pin.logic = GPIO_DIRECTION_INPUT,.pin.logic = GPIO_LOW};
interrupt_Rbx_t rb6 = {.EXT_INTERRUPT_HANDLER = int2_isr,.priority = HIGH_PRIORITY,.pin.port = PORTB_INDEX,.pin.pin = PIN6,.pin.logic = GPIO_DIRECTION_INPUT,.pin.logic = GPIO_LOW};

*/
std_ReturnType ret = E_NOT_OK;

int main() {

    application_initialize();
    /*Interrupt_INTx_Init(&int0);
    Interrupt_INTx_Init(&int1);
    Interrupt_INTx_Init(&int2);*/
    Interrupt_RBx_Init(&rb4);
   // Interrupt_RBx_Init(&rb5);
   // Interrupt_RBx_Init(&rb6);
    
    while(1){
        
        
        //counter++;
        
    }
    return (EXIT_SUCCESS);
}
void application_initialize(){
    ret = Ecu_initialize();
}
