 /*
 * Name : Suraj Roy
 * Date : 15/10/2022
 * Description : Car black box
 */


#ifndef MAIN_H
#define	MAIN_H

#include <xc.h>
#include <string.h>

#include "clcd.h"
#include "adc.h"
#include "ds1307.h"
#include "i2c.h"
#include "car_bb.h"
#include "digital_keypad.h"
#include "at24c04.h"
#include "timers.h"
#include "uart.h"

#define DASH_BOARD_FLAG     0x01
#define LOGIN_FLAG          0x02
#define LOGIN_MENU_FLAG     0x03  
#define VIEW_LOG_FLAG       0x04
#define CLEAR_LOG_FLAG      0x05
#define DOWNLOAD_FLAG       0x06
#define TIME_FLAG           0X07
#define PASSWORD_FLAG       0x08

#define RESET_PASSWORD      0x10
#define RESET_NOTHING       0x20
#define RESET_MENU          0x30
#define RESET_LOG           0x40
#define RESET_CLEAR         0x50
#define RESET_DOWNLOAD      0x60
#define RESET_TIME          0x70

#define RETURN_BACK         0x0A 
#define LOGIN_SUCCESS       0x0B
#define TASK_SUCCESS        0x0C
#define TASK_FAILURE        0x0D

#endif	/* MAIN_H */

