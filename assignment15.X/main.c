/*
 * Name : Suraj Roy
 * Date : 01/10/2022
 * Description : Implement system sleep and wake up while Interrupt on change
 */

#include <xc.h>
#include"main.h"
#include "ssd.h"
#include"external_interrupt.h"
#include"timer.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)
//global variable
 unsigned int sec = 0 ;

static void init_config(void) {
    //make PORTB as output by TRISB
    LED_ARRAY_DDR = 0x00;
    
    //making all led turn off in PORTB
    LED_ARRAY = 0x00;
    //calling function
    init_ext_int();
    init_timer0();
    init_ssd();
    PEIE = 1;
    GIE = 1;
}

void main(void) {
    
    init_config();
    static unsigned char ssd[4]={ONE, TWO, THREE, FOUR};

    while (1) {
        //display 1234 on ssd for 5 second
        if(sec < 5)
        {
             display(ssd);
        }
        //make system to go to sleep till external interrupt occurs
        else
        { 
            SLEEP();
        }   
          
    }
    return;
}