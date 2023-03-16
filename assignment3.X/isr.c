/*
 * Name : Suraj Roy
 * Date : 08/09/2022
 * Description :  Implement the time separator with Timer 0, Timer 1 and Timer 2
 */


#include <xc.h>
#include "main.h"
void __interrupt() isr(void)
{
    /*declaring variable*/
    static unsigned int count0 = 0, count1 = 0, count2 = 0;
    
    /*for TIMER0*/
    /*Check flag of TIMER0 is 1*/
    if (TMR0IF == 1)
    {
        /* TMR0 Register valur + 6 (offset count to get 250 ticks) + 2 Inst Cycle */
        TMR0 = TMR0 + 8;
        
        if (++count0 == 10000)
        {
            count0 = 0;
            
            LED0 = !LED0;
        }
        /*make flag to 0*/
        TMR0IF = 0;
    
     }

    //for TIMER1
    
    /*Check flag of TIMER1 is 1*/
    if (TMR1IF == 1)
    {
        TMR1H = 0x0B;
        TMR1L = 0xDC;
       
        if (++count1 == 40)
        {
            count1 = 0;
            
            LED1 = !LED1;
        }
        /*make flag to 0*/                
        TMR1IF = 0;
    }


    //for TIMER2
    
    /*Check flag of TIMER2 is 1*/
    if (TMR2IF == 1)
    {
        if (++count2 == 625)
        {
            count2 = 0;
            
            LED2 = !LED2;
        }
        /*make flag to 0*/
        TMR2IF = 0;
    }
}