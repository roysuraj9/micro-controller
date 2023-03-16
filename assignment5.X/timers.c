/*
 * Name : Suraj Roy
 * Date : 2/10/2022
 * Description : Implement a LED dimmer application using PWM (Timer ISR Based)
 *//


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
