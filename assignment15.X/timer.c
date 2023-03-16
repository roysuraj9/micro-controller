/*
 * Name : Suraj Roy
 * Date : 01/10/2022
 * Description : Implement system sleep and wake up while Interrupt on change
 */

#include <xc.h>

void init_timer0(void)
{
    /* Setting the internal clock source */
    T0CS = 0;
    
    /* Assinging the prescaler to Watchdog Timer */
    PSA = 1;

    TMR0 = 6;
    
    /* The timer interrupt is enabled */
    TMR0IE = 1;
}
