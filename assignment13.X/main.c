/*
 * Name : Suraj Roy
 * Date : 12/09/2022
 * Description : Self counter using SSDs with storage on key press
 */

#include <xc.h>
#include "digital_keypad.h"
#include "ssd.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

unsigned int count = 0;

static void init_config(void) {
    /*reset is press start count from stored value in eeprom*/
    count = eeprom_read(0x00) * 100 + eeprom_read(0x01);
    /*calling  digital keypad and ssd*/
    init_digital_keypad();
    init_ssd();
}

void main(void) {
    //declaring variable and array
    unsigned char ssd[MAX_SSD_CNT];
    unsigned char digits[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX,SEVEN, EIGHT ,NINE};
    unsigned char key;
    unsigned int delay = 100;
    init_config();

    while(1) {        
        key = read_digital_keypad(STATE);
        
        /*while SW2 is press then store the value of count in eeprom*/
        if(key == SW2){
        
            eeprom_write(0x00, count / 100);
            eeprom_write(0x01, count % 100);
        }
        /*non blocking delay*/
        if(delay-- == 0)
        {
            delay = 100;
            count++;
            /*if count reaches 9999 then reset to 0*/
            if(count > 9999)
                count = 0;
        }

        //display count value on ssd
        ssd[0] = digits[count/1000];
        ssd[1] = digits[((count % 1000) / 100)];
        ssd[2] = digits[((count % 100) / 10)];
        ssd[3] = digits[(count % 10)];
        
        display(ssd);
    }
    return;
}