/*
 * Name : Suraj Roy
 * Date : 21/08/2022
 * Description : Implement LED train pattern on leds
 */


#include <xc.h>
#include"main.h"

#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)

static void init_config(void) {
    //make PORTD as output by TRISD
    LED_ARRAY_DDR = 0x00;
    
    //making all led turn of in PORTD
    LED_ARRAY = 0x00;
}

void main(void) {
    //declare variable
    unsigned int wait = 0;
    unsigned char i;
   

    init_config();
    //infinite loop
    while (1) { 
        
        //set delay 
        if(wait++ == 50000)
        {
            wait = 0;
            
            //condition for left ON
            if(i <= 8)
            {
                LED_ARRAY = (LED_ARRAY << 1) | 0x01;
                i++;
            }
            
            //condition for left OFF
            if(i > 8 && i <=17 )
            {
                LED_ARRAY = LED_ARRAY << 1;
                i++;
            }
            
            //condition for right ON
            if(i > 17 && i <= 26)
            {
                LED_ARRAY = (LED_ARRAY >> 1) | 0x80;
                i++;
            }
            
            //condition for right OFF
            if(i > 26 && i <= 35)
            {
                LED_ARRAY = LED_ARRAY >> 1;
                i++;
                //reset i to 0
                if(i == 36)
                {
                    i = 0;
                }
            }   
        }  
    }    
}