/*
 * Name : Suraj Roy
 * Date : 26/08/2022
 * Description : Implement multiple patterns on LEDs controlled by switches
 */


#include <xc.h>
#include "digital_keypad.h"

void init_digital_keypad(void)
 {
        KEYPAD_PORT_DDR = KEYPAD_PORT_DDR | INPUT_LINES;
 }



unsigned char read_digital_keypad(unsigned char mode)
{
    static unsigned char once = 1;   
    if(mode == LEVEL)
    {    
        return (KEYPAD_PORT & INPUT_LINES); 
    }    
    else 
    {
        if(((KEYPAD_PORT & INPUT_LINES) != ALL_RELEASED) && once)
        {
            once = 0;
            return (KEYPAD_PORT & INPUT_LINES);
        }
        else if ((KEYPAD_PORT & INPUT_LINES) == ALL_RELEASED)
        {
            once = 1;
        }
    }
    return ALL_RELEASED;
}
