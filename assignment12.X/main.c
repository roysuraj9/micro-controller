/*
 * Name : Suraj Roy
 * Date : 29/09/2022
 * Description : Implement a 8 field password access to screen
 */

#include <xc.h>
#include "clcd.h"
#include "matrix_keypad.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

//function for compare strings
int compare(char code[], char pswd[])  
{  
    int flag = 0, i = 0;  // integer variables declaration  
    while(code[i] != '\0' && pswd[i] != '\0')  // while loop  
    {  
       if(code[i] != pswd[i])  
       {  
           flag = 1;  
           break;  
       }  
       i++;  
    }  
    if(flag == 0)  
    return 0;  
    else  
    return 1;  
}  

static void init_config(void) {
    //driver function call
    init_clcd();
    init_matrix_keypad();
}

void main(void) {
    //declare variable and initialization
    unsigned char key;
    char pswd[9];
    char i = 0, j = 5;
    //original password
    char code[] = "10101010";
    init_config();

    while (1) {
        //user can attempts 5 times
        if(j > 0){
            //read key as STATE
            key = read_matrix_keypad(STATE);  // 0 1 2 3 4 5 6 7 8 9 '*' '#'  ALL_RELEASED 
            //taking 8 character by user in from of 0 and 1
            if(i <= 7){
                //display cursor
                if(key == ALL_RELEASED){

                    clcd_print("_", LINE2(i));
                    __delay_ms(50);
                    clcd_print(" ", LINE2(i));
                    
                }
                //first line on clcd
                clcd_print(" ENTER PASSWORD ", LINE1(0));  
                //if key 1 is pressed store 0 in array pswd
               
                if(key == 1){
                    pswd[i] = '0';
                    //display * in placed of character
                    clcd_print("*", LINE2(i));
                    i++;
                }
                
                //if key 2 is pressed store 1 in array pswd
                if(key == 2){
                    pswd[i] = '1';
                    //display * in placed of character
                    clcd_print("*", LINE2(i));
                    i++;
                }
                //string end with null
                pswd[8] = '\0';
            }
            
            //if 8 character enter by user completed then pswd and code will compared   
            if(i == 8){  
                //function call for comparing
                int c = compare(code, pswd); 
                //if pswd matched code then 0 will return
                //display success message
                if(c == 0) {
                    clcd_print("EXCELLENT, YOU  ", LINE1(0));
                    clcd_print("CRACKED THE CODE", LINE2(0));
                } 
                
                //if user enter wrong password 
                else{
                    i = 0;
                    //decrease attempts by 1 every wrong code
                    if(--j>0){
                        clcd_print("WRONG PASSWORD ", LINE1(0));
                        clcd_putch(j + '0', LINE2(0)); 
                        clcd_print(" ATTEMPTS LEFT ", LINE2(1));
                        __delay_ms(2000);
                        clcd_print("                ", LINE2(0));
                    }
                }
            }
        }
        //if user attempts reached it limited
        else{
            clcd_print("ATTEMPTS REACHED", LINE1(0));
            clcd_print("RESET THE BOARD", LINE2(0));
        }
    }    
    return;
}