/*
 * Name : Suraj Roy
 * Date : 12/09/2022
 * Description : Implement a static clock on SSD using internal timer
 */

#include <xc.h>
#include "main.h"
#include"ssd.h"
void __interrupt() isr(void)
{
    /*declaring variable*/
    static unsigned long int count0 = 0;
    static unsigned int count1 = 0;
    
    /*for TIMER0*/
    /*Check flag of TIMER0 is 1*/
    if (TMR0IF == 1)
    {
        /* TMR0 Register valur + 6 (offset count to get 250 ticks) + 2 Inst Cycle */
        TMR0 = TMR0 + 8;
        
        /*blinking dot after 0.5 sec*/
        if(++count1 == 10000)
        {
            count1 = 0;
            flag = !flag;   
        }        
        /*increasing minute value after 980000 count*/
        if (++count0 == 980000)
        {
            count0 = 0;
            minute++;
        }    
        /*make flag to 0*/
        TMR0IF = 0;    
    }
}