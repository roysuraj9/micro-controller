 /*
 * Name : Suraj Roy
 * Date : 12/10/2022
 * Description : Implement a 4 digit key press counter with persistence using external EEPROM
 */

#include "i2c.h"
#include "at24c04.h"

void init_at24c04(void)
{
    unsigned char dummy;
    
    dummy = read_at24c04(SEC_ADDR);
    dummy = dummy & 0x7F;
    write_at24c04(SEC_ADDR, dummy);
}

unsigned char read_at24c04(unsigned char addr)
{
    unsigned char data;
    
    i2c_start();
    i2c_write(SLAVE_WRITE);
    i2c_write(addr);
    i2c_rep_start();
    i2c_write(SLAVE_READ);
    data = i2c_read(0);
    i2c_stop();
    
    return data;
}

void write_at24c04(unsigned char addr, unsigned char data)
{
    i2c_start();
    i2c_write(SLAVE_WRITE);
    i2c_write(addr);
    i2c_write(data);
    i2c_stop();
}

