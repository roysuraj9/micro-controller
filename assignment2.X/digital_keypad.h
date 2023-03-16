/*
 * Name : Suraj Roy
 * Date : 26/08/2022
 * Description : Implement multiple patterns on LEDs controlled by switches
 */

#ifndef DIGITAL_KEYPAD_H
#define	DIGITAL_KEYPAD_H

#define SW1          0x3E
#define SW2          0x3D
#define SW3          0x3B
#define SW4          0x37
#define SW5          0x2F
#define SW6          0X1F

#define ALL_RELEASED 0x3F

#define LEVEL        0
#define STATE        1

#define KEYPAD_PORT   PORTB
#define KEYPAD_PORT_DDR TRISB
#define INPUT_LINES     0x3F

unsigned char read_digital_keypad(unsigned char mode);
void init_digital_keypad(void);

#endif	/* DIGITAL_KEYPAD_H */

