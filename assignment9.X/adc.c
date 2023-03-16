/*
 * Name : Suraj Roy
 * Date : 23/09/2022
 * Description :  Implement a temperature sensor node with CLCD display
 */

#include <xc.h>

void init_adc(void)
{
    /* Selecting Right Justification */
    ADFM = 1;
    
    /* Starting the ADC Module */
    ADON = 1;
    
    //using LM35 on channel 2
    CHS2 = 0;
    CHS1 = 1;
    CHS0 = 0;
}

unsigned short int read_adc(void)
{
    
    unsigned short int adc_reg_val; // 2bytes
    
    /* Start the ADC conversion */
    GO = 1;
    
    /* Wait for the conversion to complete */
    while (nDONE); //nDONE = 0 GO = 0
    
   
    adc_reg_val = (ADRESH << 8) | ADRESL;  
    
    return adc_reg_val; // 0 to 1023
    
}