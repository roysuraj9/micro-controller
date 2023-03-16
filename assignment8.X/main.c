/*
 * Name : Suraj Roy
 * Date : 12/09/2022
 * Description : Implement a 4 digit key press counter
 */

#include <xc.h>
#include "ssd.h"
#include "digital_keypad.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

static void init_config(void) {
    /*calling digital keypad and ssd function*/
    init_digital_keypad();
    init_ssd();
}

void main(void) {
    /*declare variable and array*/
    unsigned char ssd[MAX_SSD_CNT];
    unsigned char digits[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX,SEVEN, EIGHT ,NINE};
    unsigned int count = 0, delay = 200;
    unsigned char key, key1;
    init_config();

    while (1) {
        /*read key as level change*/
        key1 = read_digital_keypad(LEVEL);
        /*if SW1 is long press for 2 sec then reset count to 0*/
        if(key1 == SW1){
            if(delay-- == 0){
                delay = 200;
                count=0;
            }
        }
        /*read key as state change*/
        key = read_digital_keypad(STATE);
        /*if SW1 is press then increment count by 1*/
        if(key == SW1)
        {  
            count++;
            /*if count reaches to 9999 then count change to 0*/
            if(count > 9999)
                count = 0;
        }
       
        /*display count value on ssd*/
        ssd[0] = digits[count/1000];
        ssd[1] = digits[((count % 1000) / 100)];
        ssd[2] = digits[((count % 100) / 10)];
        ssd[3] = digits[(count % 10)];
        
        display(ssd);
         
    }
    return;
}