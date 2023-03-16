/*
 * Name : Suraj Roy
 * Date : 12/09/2022
 * Description : Implement a static clock on SSD using internal timer
 */

#include <xc.h>
#include "main.h"
#include "timer.h"
#include "ssd.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)


static void init_config(void) {
   
    /*calling timer0 and ssd*/
    init_timer0();
    init_ssd();
    
    /* Peripheral Interrupt Enable Bit*/
    PEIE = 1;
    
    /* Enable all the Global Interrupts */
    GIE = 1;

}

void main(void) {
    unsigned char ssd[MAX_SSD_CNT];
    unsigned char digits[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX,SEVEN, EIGHT ,NINE};
    init_config();

    while (1) {
        /*if minute is 60 then increase hour and minute equal to 0*/
        if(minute == 60)
        {
            hour++;
            minute = 0;
        }
        /*if hour is 24 then change it to 00*/
        if(hour == 24)
        {
            hour = 0;
        }
        
        /*for hour ssd0 and ssd1 is used and for minute ssd2 and ssd3*/
        ssd[0] = digits[hour / 10];
        /*if flag is 1 then display dot at ssd1*/
        if(flag == 1)
        {
            ssd[1] = digits[hour % 10] | DOT;
        }
        else
        {
            ssd[1] = digits[hour % 10];
        }
        ssd[2] = digits[minute / 10];
        ssd[3] = digits[minute % 10];
        
        display(ssd);
    }
    return;
}