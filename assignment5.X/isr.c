/*
 * Name : Suraj Roy
 * Date : 01/10/2022
 * Description :  Using Timer based PWM, implement a LED dimmer application.
 */


#include <xc.h>
#include "main.h"
//declare a macro PERIOD
#define PERIOD     100
//using duty cycle from main function
extern int duty_cycle;

void __interrupt() isr(void)
{   
    if (TMR0IF == 1){
         /*TMR0 Register valur + 6 (offset count to get 250 ticks) + 2 Inst Cycle */
        TMR0 = TMR0 + 6 + 2;
        
        
        static unsigned int loop_counter = 0;   
        //increase brightness of led till loop counter less than duty cycle    
        if (loop_counter < duty_cycle)     
        {
            LED1 = 1;
        }
        //reducing brightness led till loop counter greater than duty cycle 
        else if(loop_counter > duty_cycle)
        {
            LED1 = 0;
        }
        //if loop counter is 100 reset to 0
        if (loop_counter++ == PERIOD)
        {
            loop_counter = 0;
        }
        TMR0IF = 0;
    }
}