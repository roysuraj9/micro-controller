 /*
 * Name : Suraj Roy
 * Date : 12/10/2022
 * Description : Implement a 4 digit key press counter with persistence using external EEPROM
 */

#ifndef AT24C04_H
#define	AT24C04_H
#define SLAVE_WRITE              0xD0
#define SLAVE_READ               0xD1

#define SEC_ADDR                0x00


void init_at24c04(void);
unsigned char read_at24c04(unsigned char addr);
void write_at24c04(unsigned char addr, unsigned char data);

#endif	/* AT24C04_H */
