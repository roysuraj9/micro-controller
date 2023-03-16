/*
 * Name : Suraj Roy
 * Date : 28/09/2022
 * Description : Implement a point brightness control
 */


#include <xc.h>
#include "main.h"
#include "timers.h"
#include "digital_keypad.h"

#define PERIOD     100

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)
//global variable
unsigned int duty_cycle = 10;

//function software_pwm
void software_pwm( unsigned int duty_cycle)
{
    static unsigned int loop_counter = 0;
    
    if (loop_counter < duty_cycle)     
    {
        LED1 = 1;
    }
    else if(loop_counter > duty_cycle)
    {
        LED1 = 0;
    }
    
    if (loop_counter++ == PERIOD)
    {
        loop_counter = 0;
    }
}
 

static void init_config(void) {
    //turn off led array
    LED_ARRAY1 = 0x00;
    LED_ARRAY1_DDR = 0x00;
    
    //calling driver function 
    init_digital_keypad();
    init_timer0();
    
    PEIE = 1;
    /* Enable all the Global Interrupts */
    GIE = 1;
}

void main(void) {
    //declare variable
    unsigned char key;
    init_config();

    while (1)
    {
        //read key as STATE change
        key = read_digital_keypad(STATE);
        
        //if sw1 is pressed then turn led to full brightness for 5 second
        if (key == SW1){
            //turn on timer
            //set brightness to 100 by setting duty cycle
            sec = 0;
            if(sec < 5){
                duty_cycle = 100;
            }
        }
        //if time out reduce brightness 10 by setting duty cycle
        if(sec >= 5)
        {
            duty_cycle = 10;
        }
        //calling pwm function
        software_pwm(duty_cycle);                  
    }
    return;
}
