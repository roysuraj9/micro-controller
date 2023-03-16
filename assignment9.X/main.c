/*
 * Name : Suraj Roy
 * Date : 23/09/2022
 * Description :  Implement a temperature sensor node with CLCD display
 */

#include <xc.h>
#include"clcd.h"
#include "adc.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

void display(unsigned short adc_reg_val)
{ 
    //declare variable and array
    char buff[3];
    int i;
    
    //convert LM35 output
    adc_reg_val = (adc_reg_val * 48) / 100;
            
    //calling clcd_print to display on line2 from 0 position
    clcd_print("TEMPERATURE:", LINE2(0));  

    //extracting digit one by one 
    //convert digit into convert and in buff 
    i = 1;
    do
    {
        buff[i] = (adc_reg_val % 10) + '0';//27%10 -> 7 + '0' 
        adc_reg_val = adc_reg_val / 10;
       
    } while (i--);
    //store last character as null
    buff[2] = '\0';
    
    //display buff output
    clcd_print(buff, LINE2(12));
    //display degree symbol and C
    clcd_putch((char)223, LINE2(14));
    clcd_print("C", LINE2(15));
}

static void init_config(void) {
    //function call
    init_clcd();
    init_adc();
}

void main(void) {
    unsigned short adc_reg_val; //0 to 1023
    init_config();
    //display message on line1
    clcd_print("LM35 TEMP SENSOR", LINE1(0));
    
    while (1) {
        //read 10 bit data from adc LM35 
        adc_reg_val = read_adc();//10 bits -> 0 to 1023
        //function call sending adc_reg_val
        display(adc_reg_val);
    }
    return;
}