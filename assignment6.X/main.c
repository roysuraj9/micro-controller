/*
 * Name : Suraj Roy
 * Date : 2/10/2022
 * Description : Implement a LED dimmer application using PWM (Timer ISR Based)
 */


#include <xc.h>
#include "main.h"
#include "adc.h"
#include "timers.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)
//declare duty cycle as global
int duty_cycle ;


static void init_config(void) {
    //making led as output device and turn off
    LED_ARRAY = 0x00;
    LED_ARRAY_DDR = 0x00;
    
    init_timer0();
    init_adc();
     /* Enable all the Global Interrupts */
    GIE=1;
}

void main(void) {
    unsigned short adc_reg_val; //0 to 1023
    
    init_config();

    while (1) {
        //read Knob of potentiometer output and divide it by 10.23
        //assigning to duty cycle
        duty_cycle = read_adc() / 10.23;//10 bits -> 0 to 1023    
    }
    return;
}
