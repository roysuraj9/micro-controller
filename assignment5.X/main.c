/*
 * Name : Suraj Roy
 * Date : 01/10/2022
 * Description :  Using Timer based PWM, implement a LED dimmer application.
 */


#include <xc.h>
#include "main.h"
#include "digital_keypad.h"
#include "timers.h"
//declare duty cycle as global at 50% of duty cycle
static int duty_cycle = 50;

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)


static void init_config(void) {
    //making led as output device and turn off
    LED_ARRAY = 0x00;
    LED_ARRAY_DDR = 0x00;
    //call function
    init_timer0();
    init_digital_keypad();
   
    /* Enable all the Global Interrupts */
    GIE =1;
}

void main(void) {
    //declare variable
    unsigned char key; 
    unsigned long int wait = 500;
    init_config();

    while (1) {
        //read key as level change
        key = read_digital_keypad(LEVEL);
        
        if(wait-- == 0){
            wait = 500;
            //if SW1 is pressed increase duty cycle
            if(key == SW1)
            {
                if(duty_cycle != 100)
                {
                    duty_cycle++;
                }
            }
            //if SW2 is pressed decrease duty cycle
            if(key == SW2)
            {
                if(duty_cycle != 0)
                {
                    duty_cycle--;
                }
            }
        }
    }
    return;
}