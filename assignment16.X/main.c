/*
 Name : Suraj Roy
 Date : 10/10/2022
 Description : Implement a message display using UART and CLCD 
 */

#include <xc.h>
#include "uart.h"
#include "clcd.h"
#include "string.h"
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

//Receive a character until newline
void getstr(char *str)  

{
    unsigned char i=0,j=0;
    do
    {
        *(str+i)= getchar();
        j = *(str+i);
        i++;
    }
    while(j != '\n' && j != '\r');
    i++;
    *(str+i) = '\0';
}

static void init_config(void) {

    //calling function
    init_clcd();
    init_uart(9600);
    
    puts("UART Test Code\n\r");
    
    /* Enabling peripheral interrupt */
    PEIE = 1;    
    /* Enabling global interrupt */
    GIE = 1;
}

void main(void) {
    //declare variables
    char str[90]="", str1[17]="", str2[17]="";
    unsigned int i = 0, j=0;
    init_config();

    while (1) {
        //calling function
        getstr(str);
        
        while(i < strlen(str))
        {
            //if string enter is of 16 or less store in str1
            if(i < 16)
            {
                str1[i] = str[i];
            }
            //if string enter is of 32 or less store in str2
            if(i >= 16 && i < 32)
            {
                str2[i-16] = str[i];    
            }
            //if string enter is of 32+
            //store str2 element in str1 and store new character in str2
            if(i >= 32)
            {
                if(j == 0)
                {
                    strncpy(str1,"",strlen(str1));
                    strncpy(str1,str2,16);
                    strncpy(str2,"",strlen(str2));
                    j=1;
                }
                str2[i-32] = str[i];
            }
            i++;
        }
        //convert character of array in string
        str1[16] = '\0';
        str2[16] = '\0';
        strncpy(str,"",strlen(str));
        clear_screen();
        //display output on clcd
        clcd_print(str1,LINE1(0));
        clcd_print(str2,LINE2(0));
    }
    return;
}
