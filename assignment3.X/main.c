/*
 * Name : Suraj Roy
 * Date : 08/09/2022
 * Description :  Implement the time separator with Timer 0, Timer 1 and Timer 2
 */

#include <xc.h>
#include "main.h"
#include "timer.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

static void init_config(void) {
    /*consider led is OFF*/
    LED_ARRAY1 = 0x00;
    LED_ARRAY1_DDR = 0x00;
    
    /*call functions*/
    init_timer0();
    init_timer1();
    init_timer2();
    
    /* Peripheral Interrupt Enable Bit*/
    PEIE = 1;
    
    /* Enable all the Global Interrupts */
    GIE = 1;
}

void main(void) {
    init_config();

    while (1) {
        ;
    }
    return;
}