 /*
 * Name : Suraj Roy
 * Date : 12/10/2022
 * Description : Implement a 4 digit key press counter with persistence using external EEPROM
 */

#include <xc.h>
#include "ssd.h"
#include "digital_keypad.h"
#include "i2c.h"
#include "at24c04.h"
#pragma config WDTE = OFF

//declare count as static
static unsigned count  = 0;

void init_config(void)
{
    //calling init function
	init_ssd();
	init_digital_keypad();
    init_i2c(100000);
    init_at24c04();
    //read eeeprom address
    count = 1000 * read_at24c04(0x01) + 100 * read_at24c04(0x02) + 10 * read_at24c04(0x03) + read_at24c04(0x04);
}


void main(void)
{
    init_config();
    
    static unsigned char ssd[MAX_SSD_CNT]={ZERO,ZERO,ZERO,ZERO};
    static unsigned char digit[] = {ZERO, ONE,TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
	unsigned char key, key1, wait = 200 ;
    
	while(1)
	{
		key = read_digital_keypad(STATE);
        key1 = read_digital_keypad(LEVEL);
        
        
		/* if switch 1 pressed increment counter by 1 */
		if ( key == SW1 )
		{
                count++;
                if (count > 9999) 
                {
                    count = 0;
                }
        }
        //store count in eeprom whenSW2 pressed
        else if (key == SW2)
        {
            /*writing every digit in eeprom*/
            write_at24c04(0x04, (count % 10));
            write_at24c04(0x03, ((count % 100)/10));
            write_at24c04(0x02, ((count % 1000)/100));
            write_at24c04(0x01, (count / 1000));
        }
        
		/* if switch 1 pressed for long than reset counter */
        if(wait-- == 0)
        {
            wait = 200;
            if(key1 == SW1)
            {
                count = 0;
            }
        }
        /*displaying the digit in ssd */
        
        ssd[3] = digit[count % 10];
		ssd[2] = digit[(count % 100)/10];
		ssd[1] = digit[(count % 1000)/100];
        ssd[0] = digit[count / 1000];    
        display(ssd);
	}
}