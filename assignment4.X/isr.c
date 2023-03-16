/*
 * Name : Suraj Roy
 * Date : 28/09/2022
 * Description : Implement a point brightness control
 */


#include <xc.h>
#include "main.h"

void __interrupt() isr(void)
{
    static unsigned int count = 0;
    
    if (TMR0IF == 1)
    {
        /* TMR0 Register valur + 6 (offset count to get 250 ticks) + 2 Inst Cycle */
        TMR0 = TMR0 + 6 + 2;
        
        if (++count == 20000)
        {
            count = 0;
            //increement second
            sec++;
        }
        
        TMR0IF = 0;
    }
}
