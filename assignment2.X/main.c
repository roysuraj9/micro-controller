/*
 * Name : Suraj Roy
 * Date : 26/08/2022
 * Description : Implement multiple patterns on LEDs controlled by switches
 */


#include <xc.h>
#include "main.h"
#include "digital_keypad.h"

#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)

static void init_config(void) {
    LED_ARRAY1 = OFF;
    LED_ARRAY1_DDR = OFF;
    
    init_digital_keypad();
}

void main(void) {
    //declare varaibles
    unsigned char key;
    unsigned long int wait = 0;
    unsigned char i, flag = 0;
    
    init_config();
    while(1){
        //call function read_digital_keypad and itf value to key
        key = read_digital_keypad(STATE);
        
        //compare key and change flag value
        if(key == SW1)
        {
            LED_ARRAY1 = OFF;
            flag = 1;
            i = 0;
        }
        
        if(key == SW2)
        {
            LED_ARRAY1 = OFF;
            flag = 2;
            i = 0;
        }
        
        if(key == SW3)
        {
            LED_ARRAY1 = OFF;
            flag = 3;
            i = 1;
        }
        
        if(key == SW4)
        {
            LED_ARRAY1 = OFF;
            flag = 4;
            i = 1;
        }
        
        //non-blocking delay
        if (wait++ == 50000)
        {
            wait = 0; 
            
            //if SW1 is pressed 
            if(flag == 1)
            {
                //condition for left ON
                if(i <= 8)
                {
                    LED_ARRAY1 = (LED_ARRAY1 << 1) | 0x01;
                    i++;
                }
                //condition for left OFF
                if(i > 8 && i <= 17 )
                {
                    LED_ARRAY1 = LED_ARRAY1 << 1;
                    i++;
                }
                //condition for right ON
                if(i > 17 && i <= 26)
                {
                    LED_ARRAY1 = (LED_ARRAY1 >> 1) | 0x80;
                    i++;
                }
                //condition for right OFF
                if(i > 26 && i <= 35)
                {
                    LED_ARRAY1 = LED_ARRAY1 >> 1;
                    i++;
                    //reset i to 0
                    if(i == 36)
                    {
                        i = 0;
                    }
                }
            }
            
            //if SW2 is pressed 
            if(flag == 2)
            {
                //condition for left ON
                if(i <= 8)
                {
                    LED_ARRAY1 = (LED_ARRAY1 << 1) | 0x01;
                    i++;
                }
                //condition for left OFF
                if(i > 8 && i <= 17 )
                {
                    LED_ARRAY1 = LED_ARRAY1 << 1;
                    i++;
                    if(i == 18)
                    {
                        i = 0;
                    }
                }
            }
            
            //if SW3 is pressed run leds blink alternately
            if(flag == 3)
            {
                if(i == 1)
                {
                    LED_ARRAY1 = 0xAA;
                }
                if(i == 2)
                {
                    LED_ARRAY1 = 0x55;
                    i = 0;
                }
                i++;
            }
    
            //if SW4 is pressed nibble pattern generate
            if(flag == 4)
            {
                if(i == 1)
                {
                    LED_ARRAY1 = 0x0F;
                }
                if(i == 2)
                {
                    LED_ARRAY1 =  0xF0;
                    i = 0;
                }
                i++;
            }
        }
    }
    return;
}