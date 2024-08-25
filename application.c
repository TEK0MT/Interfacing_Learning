 /* 
 * File:   application.c
 * Author: MOHAMED TAREK
 *
 * Created on April 22, 2024, 5:31 AM
 */


#include "application.h"
std_ReturnType ret = E_NOT_OK;
void isr(void){
    led_turn_toggle(&led1);
}
timer2_t timer = {.TIMER2_HANDLER = NULL,.prescaler_val = TIMER2_PRESCALER_OFF,.postscale_val = TIMER2_POSTSCALER_DIV_BY_4,.prevalue = 249};
ccp_t ccp = {.ccpx = CCP1_INST,.pin.port = PORTC_INDEX,.pin.pin = PIN2,.pin.direction = GPIO_DIRECTION_OUTPUT,.pin.logic = GPIO_LOW,.timer2_pre_scaler = TIMER2_CCP_PRESCALER_OFF,.timer2_postscaler = TIMER2_CCP_POSTSCALER_DIV_BY_4
,.pwm_freq = 1000,.variant = CCP_PWM,.mode = CCP_PWM_MODE,.Interrupt_CCP1_Handler = NULL,.Interrupt_CCP2_Handler = NULL};
uint8 value = 0;
int main() {
    application_initialize();
    TIMER2_INIT(&timer);
    CCP_Init(&ccp);
    CCP_PWM_Set_Duty(&ccp,50);
    CCP_PWM_Start(&ccp);
    while(1){
        
    }
    return (EXIT_SUCCESS);
}
void application_initialize(){
    ret = Ecu_initialize();
}
