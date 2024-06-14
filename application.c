/* 
 * File:   application.c
 * Author: MOHAMED TAREK
 *
 * Created on April 22, 2024, 5:31 AM
 */


#include "application.h"
/*
 * 
 */





typedef union
{
    struct
    {
        unsigned SELF_LATC0 :1;
        unsigned SELF_LATC1 :1;
        unsigned SELF_LATC2 :1;
        unsigned SELF_LATC3 :1;
        unsigned SELF_LATC4 :1;
        unsigned SELF_LATC5 :1;
        unsigned SELF_LATC6 :1;
        unsigned SELF_LATC7 :1;
    };
    uint8 LATC_REGISTER;
}SELF_LATC;
#define SELF_LATC_REGISTER ((volatile SELF_LATC *)(0xF8B))
int main() {
    TRISC = 0x00;
    SELF_LATC_REGISTER->LATC_REGISTER = 0x55;
    
    
    while(1)
    {
    __delay_ms(2000);
    SELF_LATC_REGISTER->SELF_LATC5 = 1;
    __delay_ms(2000);
    SELF_LATC_REGISTER->SELF_LATC5 = 0;    
    }
    return (EXIT_SUCCESS);
}

