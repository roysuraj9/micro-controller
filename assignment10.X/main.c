/*
 * Name : Suraj Roy
 * Date : 12/09/2022
 * Description : Implement a scrolling number marquee with direction control
 */

#include <xc.h>
#include "digital_keypad.h"
#include "ssd.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)


static void init_config(void) {
    /*calling function digital keypad and ssd*/
    init_digital_keypad();
    init_ssd();
}

void main(void) {
    /*declare variable*/
    unsigned char ssd[MAX_SSD_CNT];
    unsigned char digits[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX,SEVEN, EIGHT, NINE, BLANK, BLANK};
    unsigned int delay = 50, count = 0, flag = 0, s_flag = 0, stop_flag = 0;
    unsigned char key;
    init_config();

    while (1) {
        /*read switch as state*/
        key = read_digital_keypad(STATE);
        
        /*setting flag*/
        if(key == SW1){
            flag = 1;
        }
        if(key == SW2){
            flag = 2;
        } 
        if(key == SW3){
            s_flag = !s_flag;
            if(s_flag == 1){
                stop_flag = 1;
            }
            else{
                stop_flag = 0;
            }
        }
        
        if(stop_flag == 0){
            /*inital scrolling and which SW1 is press number left to right*/
            if(flag == 0 || flag == 1){
                /*delay of 0.5 hz*/
                if(delay-- == 0){
                    delay = 50;
                    /*increment count if count is equal to 13 then reset count to 0*/
                    if(++count == 13)
                        count=0;
                }
            }
            /*scrolling number right to left when SW2 is pressed*/
            if(flag == 2){
                if(delay-- == 0){
                    delay = 50;
                    /*decrement count if count is equal to -1 then reset count to 0*/
                    if(--count == -1)
                        count=12;
                }
            }
        }
       /*when SW3 is press stop scrolling*/
        if(stop_flag == 1){
            count = count;
        }
        
        /*display value of count on ssd*/
        ssd[0] = digits[count % 12];
        ssd[1] = digits[((count + 1) % 12)];
        ssd[2] = digits[((count + 2) % 12)];
        ssd[3] = digits[((count + 3) % 12)];
        
        display(ssd);
    }
    return;
}
