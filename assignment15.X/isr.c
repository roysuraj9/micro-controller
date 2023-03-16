/*
 * Name : Suraj Roy
 * Date : 01/10/2022
 * Description : Implement system sleep and wake up while Interrupt on change
 */

#include <xc.h>
#include "main.h"

extern unsigned int sec;

void __interrupt() isr(void)
{
    /*declaring variable*/
    static unsigned int count = 0;

    
    //external interupt
    if (INTF == 1)
    {
        sec = 0; 
        INTF = 0;
    }
    
    if (TMR0IF == 1){
        /* TMR0 Register valur + 6 (offset count to get 250 ticks) + 2 Inst Cycle */
        TMR0 = TMR0 + 8;
        
        //increment sec value after one second 
        if(++count == 20000) {
            count = 0;
            sec++; 
        }    
        //blinking led every one second
        if(sec < 5)
        {
            if(count == 0)
            {
                 LED2 = !LED2;
            }
        }
         TMR0IF = 0; 
    }    
}