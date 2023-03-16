 /*
 * Name : Suraj Roy
 * Date : 15/10/2022
 * Description : Car black box
 */

#include <xc.h>
#include "main.h"

unsigned char min;
extern unsigned char return_time;
void __interrupt() isr(void)
{
    static unsigned long int count = 0;
    
    if (TMR2IF == 1)
    {
        if (++count == 73000)
        {
            count = 0;
            if(min > 0)
            {
                min--;
            }
            if(min == 0 && return_time > 0)
            {
                return_time--;
            }
        }
        
        TMR2IF = 0;
    }
}