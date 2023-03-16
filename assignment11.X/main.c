/*
 * Name : Suraj Roy
 * Date : 23/09/2022
 * Description : Implement a right scrolling message marquee
 */

#include <xc.h>
#include "clcd.h"

#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)

static void init_config(void) {
    //function call
    init_clcd();
}

void main(void) {
    //declare variables
    char temp;
    long int j = 0;
    //character array
    char msg[] = "scrolling demo  ";
    
    init_config();
 
    clcd_print("RIGHT MARQUEE", LINE1(2));
    while (1) {
        //delay 0.5 hz
        if(j++ == 10000){
            j = 0;
            
            //store last character in temp
            temp = msg[15];
            //shift msg one place right 
            for(int i = 15; i > 0; i--)
            {
                msg[i] = msg[i - 1];
            }
            msg[0]= temp;
            //display msg on clcd
            clcd_print(msg, LINE2(0));
        }
    }
    return;
}