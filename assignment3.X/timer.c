/*
 * Name : Suraj Roy
 * Date : 08/09/2022
 * Description :  Implement the time separator with Timer 0, Timer 1 and Timer 2
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

void init_timer1(void)
{   
    /*selecting timer mode*/
    TMR1CS = 0;
    
    /*enable  TIMER1 mode*/
    TMR1ON = 1;

    T1OSCEN = 1; 
    
    /*assigning the initial value to the timer*/
    
    TMR1H = 0x0B;
    TMR1L = 0xDC;
            
    /* The timer interrupt is enabled */
    TMR1IE = 1;

}
void init_timer2(void)
{
    /* Selecting the scale as 1:16 */
    T2CKPS0 = 1;
    T2CKPS1 = 1;

    /* Loading the Pre Load register with 250 */
    PR2 = 250;
    
    /* The timer interrupt is enabled */
    TMR2IE = 1;
       
    /* Switching on the Timer2 */
    TMR2ON = 1;
}