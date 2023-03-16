/*
 Name : Suraj Roy
 Date : 09/10/2022
 Description : Implement a dynamic scrolling number marquee with rotation control
 */
#include <xc.h>
#include "clcd.h"
#include "matrix_keypad.h"
#include "string.h"
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

static void init_config(void) {
    //calling init function
    init_clcd();
    init_matrix_keypad();
    
    clcd_print("enter the number", LINE1(0));
    
}

void main(void) {
    //declare variable
    unsigned char key, temp;
    static char msg[16];
    static int flag = 0, edit_key = 1, once = 1, size = 0;
    static char scr[17]= "                ";
    init_config();

    while (1) {
        key = read_matrix_keypad(STATE);  // 0 1 2 3 4 5 6 7 8 9 '*' '#'  ALL_RELEASED
        
        //exit edit mode and start scrolling 
        if(key == 3)
        {
            edit_key = 0;
            clear_screen();
            clcd_print("scrolling marque", LINE1(0));
        }
        //stop scrolling
        if(key == 4)
        {
            edit_key = 1;
            clear_screen();
            clcd_print("enter the number", LINE1(0));
            clcd_print("msg:", LINE2(0));
            clcd_print(msg, LINE2(4));
            
        }
        //edit mode
        if(edit_key ==1){   
            if(once)
            {
                size = 0;
                msg[size] = '0';
                clcd_print("enter the number", LINE1(0));
                clcd_print("msg:", LINE2(0));
                clcd_putch(msg[0], LINE2(size + 4));
                once = 0;
            }
            //increment count value
            if(key == 1)
            {
                msg[size]++;
                if(msg[size] > '9')
                    msg[size] = '0';
                if(msg[size] < '0')
                    msg[size] = '9';
                
                clcd_putch(msg[size], LINE2(4 + size));
            }
            //decrement count value 
            if(key == 2)
            {
                msg[size]--;
                if(msg[size] > '9')
                    msg[size] = '0';
                if(msg[size] < '0')
                    msg[size] = '9';
                
                clcd_putch(msg[size], LINE2(4 + size));
            }
            //insert new character
            if(key == 5)
            {
                size++;
                msg[size] = '0';
                if(size > 10)
                    size = 10;
                    
                clcd_putch(msg[size], LINE2(4 + size));
            }
            //remove character
            if(key == 6)
            {            
                msg[size] = '0';            
                clcd_putch(0x00, LINE2(4 + size));            
                size--;
                if(size < 0)
                    size = 0;
            }            
            scr[size] = msg[size];
        }
        
        //scroll mode
        else if(edit_key == 0)
        {
            scr[16] = '\0';
            clcd_print("  scrolling     ", LINE1(0));
        
            if(key == 1){
                flag = 0;
            }
            if(key == 2){
                flag = 1;
            }
            
            //right scroll
            if(flag == 0){
                //delay 0.5 hz
                __delay_ms(50);
                temp = scr[15];
                //shift msg one place right 
                for(int p = 15; p > 0; p--)
                {
                    scr[p] = scr[p - 1];
                }
                scr[0]= temp;
            }
            //left scroll
            if(flag == 1){
                __delay_ms(50);
                temp = scr[0];
                //shift msg one place right 
                for(int p = 0; p < 15; p++)
                {
                    scr[p] = scr[p + 1];
                }
                scr[15] = temp;              
            }
             //display msg on clcd 
            clcd_print(scr, LINE2(0));
        }         
    }
    return;
}