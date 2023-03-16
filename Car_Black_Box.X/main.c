 /*
 * Name : Suraj Roy
 * Date : 15/10/2022
 * Description : Car black box
 */



#include "main.h"
#include "timers.h"

#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
char *gear[] = {"GN", "GR", "G1", "G2", "G3", "G4"};
char menu_pos = 0;

static void init_config(void) {
    //calling init function
    init_clcd();
    init_adc();
    init_i2c(100000);
    init_ds1307();
    init_digital_keypad();
    init_timer2();
    init_uart(9600);
    //enable interruots
    GIE = 1;
    PEIE = 1;
}

void main(void) {
    //initailazed variable
    unsigned char control_flag = DASH_BOARD_FLAG, reset_flag; //dashboard
    unsigned char event[3] = {"ON"};
    unsigned char speed = 0, key, gr = 0;
    unsigned long int wait_time = 0;   // char menu_pos =0;
    init_config();//calling initializing function

    //pre store password
    eeprom_at24c04_str_write(0x00, "1010");
    log_car_event(event, speed); //time event speed HHMMSSEVSP
    while (1) { 
        //reading speed from pot1
        speed = read_adc() / 10;
        if(speed > 99)
        {
            speed = 99;
        }
        //reading key as state
        key = read_digital_keypad(STATE);
        //sw1 is pressed collision take
        if(key == SW1)
        {
            strcpy(event, "C ");
            log_car_event(event, speed);
        }
        //changing gear by sw2 and sw3
        else if(key == SW2 && gr < 6)//char *gear[] = {"GN", "GR", "G1", "G2", "G3", "G4"};
        {
            strcpy(event, gear[gr]);//up gearing
            gr++;
            log_car_event(event, speed);
        }
        else if(key == SW3 && gr > 0)
        {
            gr--;//down gearing
            strcpy(event, gear[gr]);
            log_car_event(event, speed);
        }
        //if sw4 or sw5 pressed enter password
        else if((key == SW4 || key == SW5) && control_flag == DASH_BOARD_FLAG)
        {
            clear_screen();
            clcd_print(" Enter Password", LINE1(0));
            clcd_write(CURSOR_POS, INST_MODE);
            clcd_write(DISP_ON_AND_CURSOR_ON, INST_MODE);
            __delay_us(100);
            control_flag = LOGIN_FLAG;
            reset_flag = RESET_PASSWORD;
            TMR2ON = 1;
        }
        //if sw6 is enter in menu option
        else if(key == SW6 && control_flag == LOGIN_MENU_FLAG )
        {
            switch(menu_pos)
            {
                //view logs
                case 0:
                    clear_screen();
                    clcd_print("Logs", LINE1(0));
                    control_flag = VIEW_LOG_FLAG;
                    reset_flag = RESET_LOG;
                    break;
                    
                //clear logs
                case 1:
                    clear_screen();
                    control_flag = CLEAR_LOG_FLAG;
                    reset_flag = RESET_CLEAR;
                    break;
                //download logs on uart    
                case 2:
                    clear_screen();
                    control_flag = DOWNLOAD_FLAG;
                    reset_flag = RESET_DOWNLOAD;
                    break;
               
                    //change password    
                case 3:                                  
					log_car_event("CP",speed);
					clear_screen();
					control_flag = PASSWORD_FLAG;
					reset_flag = RESET_PASSWORD;
					TMR2ON = 1;
					break;
                   
                    // set time
                case 4 :                               
					log_car_event("CT",speed);
					clear_screen();
					control_flag = TIME_FLAG;
					reset_flag = RESET_TIME;
					break;
            }
        }
        //return to dashboard
        if ( key == SW1 && (control_flag == LOGIN_MENU_FLAG ||control_flag == VIEW_LOG_FLAG))
        {
            clear_screen();
            control_flag = DASH_BOARD_FLAG;
            reset_flag = RETURN_BACK;
        }
        //return to login menu from view log
        if ( key == SW2  && control_flag == VIEW_LOG_FLAG )
        {
            clear_screen();
            control_flag = LOGIN_MENU_FLAG;
            reset_flag =RESET_LOG;
        }

        //depend on control_flag calling function
        switch(control_flag)
        {
            case DASH_BOARD_FLAG:
                display_dashboard(event, speed);
                break;
            case LOGIN_FLAG:
                switch (login(key, reset_flag))
                {
                    case RETURN_BACK:
                        control_flag = DASH_BOARD_FLAG;
                        TMR2ON = 0;
                        clcd_write(DISP_ON_AND_CURSOR_OFF, INST_MODE);
                        __delay_us(100);
                        break;
                        
                    case LOGIN_SUCCESS:
                        control_flag = LOGIN_MENU_FLAG;
                        reset_flag = RESET_MENU;
                        TMR2ON = 0;
                        clcd_write(DISP_ON_AND_CURSOR_OFF, INST_MODE);
                        __delay_us(100);
                        continue;
                        break;
                }
                break;
            case LOGIN_MENU_FLAG:
                menu_pos = login_menu(key, reset_flag);
                break;
                
                //calling function for view log
            case VIEW_LOG_FLAG:
                clcd_write(DISP_ON_AND_CURSOR_OFF, INST_MODE);
                view_log(key, reset_flag);
                break;
                
                ////calling function for clear log 
            case CLEAR_LOG_FLAG:
                if ( clear_log(reset_flag) == TASK_SUCCESS )
					wait_time = 50;
                
				if (wait_time > 0 && --wait_time == 0 )
				{
                    //return to login menu
					control_flag = LOGIN_MENU_FLAG;
					reset_flag = RESET_MENU;
                    clear_screen();
					continue;
				}
                break;
                //calling function for download logs
            case DOWNLOAD_FLAG:
                download_log();
                //return to login menu
                control_flag = LOGIN_MENU_FLAG;
                reset_flag = RESET_MENU;
                break;
                
                //calling function for change password
            case PASSWORD_FLAG:
                switch ( change_password( key ,reset_flag ) )
				{
                    //return to dashboard
					case TASK_SUCCESS :
                        wait_time = 50;
                        control_flag = DASH_BOARD_FLAG;
                        DISP_ON_AND_CURSOR_OFF;
                        break;
                    //return to login menu
					case RETURN_BACK :
                        control_flag = LOGIN_MENU_FLAG;
                        reset_flag = RESET_MENU;
                        DISP_ON_AND_CURSOR_OFF;
                        continue;
				}

				if (wait_time > 0 && --wait_time == 0 )
				{
                    //return to login menu
					control_flag = LOGIN_MENU_FLAG;
					reset_flag = RESET_MENU;
                    clear_screen();
					continue;
				}
				break;

           //caliing function for set time
            case TIME_FLAG:
                if ( set_time( key ,reset_flag ) == TASK_SUCCESS )
					wait_time = 50;
                
				if (wait_time-- == 0 )
				{
					control_flag = LOGIN_MENU_FLAG;
					reset_flag = RESET_MENU;
                    clear_screen();
					continue;
				}
				break;

               
        }
        reset_flag = RESET_NOTHING; 
    }
}