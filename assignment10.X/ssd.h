/*
 * Name : Suraj Roy
 * Date : 12/09/2022
 * Description : Implement a scrolling number marquee with direction control
 */



#ifndef SSD_H
#define	SSD_H

#define MAX_SSD_CNT                 4

#define SSD_DATA_PORT_DDR           TRISD
#define SSD_CONTROL_PORT_DDR        TRISA

#define SSD_DATA_PORT               PORTD
#define SSD_CONTROL_PORT            PORTA

/* For Common Cathode Display */
#define ZERO   0x3F 
#define ONE    0x06
#define TWO    0x5B
#define THREE  0x4F
#define FOUR   0x66
#define FIVE   0x6D
#define SIX    0x7D
#define SEVEN  0x07
#define EIGHT  0x7F
#define NINE   0x6F
#define BLANK  0x00

void init_ssd(void);
void display(unsigned char data[]);

#endif	/* SSD_H */

