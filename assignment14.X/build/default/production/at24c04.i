# 1 "at24c04.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files (x86)/Microchip/MPLABX/v5.35/packs/Microchip/PIC16Fxxx_DFP/1.2.33/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "at24c04.c" 2






# 1 "./i2c.h" 1
# 12 "./i2c.h"
void init_i2c(unsigned long baud);
void i2c_start(void);
void i2c_rep_start(void);
void i2c_stop(void);
unsigned char i2c_read(unsigned char ack);
int i2c_write(unsigned char data);
# 7 "at24c04.c" 2

# 1 "./at24c04.h" 1
# 15 "./at24c04.h"
void init_at24c04(void);
unsigned char read_at24c04(unsigned char addr);
void write_at24c04(unsigned char addr, unsigned char data);
# 8 "at24c04.c" 2


void init_at24c04(void)
{
    unsigned char dummy;

    dummy = read_at24c04(0x00);
    dummy = dummy & 0x7F;
    write_at24c04(0x00, dummy);
}

unsigned char read_at24c04(unsigned char addr)
{
    unsigned char data;

    i2c_start();
    i2c_write(0xD0);
    i2c_write(addr);
    i2c_rep_start();
    i2c_write(0xD1);
    data = i2c_read(0);
    i2c_stop();

    return data;
}

void write_at24c04(unsigned char addr, unsigned char data)
{
    i2c_start();
    i2c_write(0xD0);
    i2c_write(addr);
    i2c_write(data);
    i2c_stop();
}
