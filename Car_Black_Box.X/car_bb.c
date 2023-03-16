 /*
 * Name : Suraj Roy
 * Date : 15/10/2022
 * Description : Car black box
 */

#include "main.h"

char overflow = 0;
unsigned char clock_reg[3];
unsigned char time[7];
unsigned char log[11];
char pos = -1;
int event_count;
extern unsigned char min;
unsigned char return_time = 5;
char *menu[] = {"View log", "Clear log", "Download log", "Change password", "Set time"};

//read time from RTC
static void get_time()
{
    clock_reg[0] = read_ds1307(HOUR_ADDR);//HH -> BCD
    clock_reg[1] = read_ds1307(MIN_ADDR); //MM -> BCD
    clock_reg[2] = read_ds1307(SEC_ADDR); //SS -> BCD
    
    time[0] = ((clock_reg[0] >> 4) & 0x03) + '0';
    time[1] = (clock_reg[0] & 0x0F) + '0';
    // MM 
    time[2] = ((clock_reg[1] >> 4) & 0x07) + '0';
    time[3] = (clock_reg[1] & 0x0F) + '0';
    // SS
    time[4] = ((clock_reg[2] >> 4) & 0x07) + '0';
    time[5] = (clock_reg[2] & 0x0F) + '0';
    time[6] = '\0';
}
//function for time on clcd
void display_time(void)
{
    get_time(); //get the time
    
    clcd_putch(time[0], LINE2(2)); // HH:MM:SS
    clcd_putch(time[1], LINE2(3));
    clcd_putch(':', LINE2(4));
    clcd_putch(time[2], LINE2(5));
    clcd_putch(time[3], LINE2(6));
    clcd_putch(':', LINE2(7));
    clcd_putch(time[4], LINE2(8));
    clcd_putch(time[5], LINE2(9));
}
//function for dashboard
void display_dashboard(unsigned char event[], unsigned char speed)
{
    clcd_print("  TIME     E  SP", LINE1(0));
    display_time();
    //event
    clcd_print(event, LINE2(11));
    //speed
    clcd_putch(speed / 10 + '0', LINE2(14));
    clcd_putch(speed % 10 + '0', LINE2(15));
}

//function log event
void log_event(void)
{
    char addr = 0x05;
    pos++;
    if(pos == 10)
    {
        pos = 0;
        
        overflow =1;
    }
    //address increement by pos
    addr = pos * 10 + 5;
    eeprom_at24c04_str_write(addr, log);
    
    //max 10 event
    if(event_count < 9)
    {
        event_count++;
    }
}

void log_car_event(char event[],unsigned char speed)
{
    //HHMMEVSP
    get_time();
    strncpy(log, time, 6); //HHMMSS
    strncpy(&log[6], event, 2); //EV
    log[8] = (speed / 10) + '0'; //first digit of speed
    log[8] = (speed % 10) + '0'; //second digit of speed
    log[10] = '\0';
    log_event();
}

//function for clear 
void clear_screen(void)
{
    clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
    __delay_us(500);
}

//function for login password
unsigned char login(unsigned char key, unsigned char reset_flag)
{
    static char npassword[4], i;
    char spassword[4];
    static unsigned char attempts_rem = 3;
    //max 3 attempts
    if(reset_flag == RESET_PASSWORD)
    {
        attempts_rem = 3;
        npassword[0] ='\0';
        npassword[1] ='\0';
        npassword[2] ='\0';
        npassword[3] ='\0';
        i = 0;
        key = 0xFF;
        
        return_time = 5;
    }
    //wait for 5 sec for next character if time up return dashboard
    if(return_time == 0)
    {
        return RETURN_BACK;
    }
    //enter password 0 &1 and display * in clcd
    if(key == SW4 && i < 4)
    {
        npassword[i] = '1';
        clcd_putch('*', LINE2(6 + i));
        i++;
        return_time = 5;
    }
    else if(key == SW5 && i < 4)
    {
        npassword[i] = '0';
        clcd_putch('*', LINE2(6 + i));
        i++;
        return_time = 5;
    }
    if(i == 4)//done entering the password
    {
        //read  the  system password
        for(int j = 0; j < 4; j++)
        {
            spassword[j] = eeprom_at24c04_random_read(j);
        }
        //compare enter password to store password in eeprom
        if(strncmp(spassword, npassword, 4) == 0)
        {
            return LOGIN_SUCCESS;//MENU_screen
        }               
        else
        {
            attempts_rem--;
            if(attempts_rem == 0)
            {
                //lock the user for 15 min
                min = 15;
                clear_screen();
                clcd_write(DISP_ON_AND_CURSOR_OFF, INST_MODE);
                __delay_us(100);
                clcd_print(" You are blocked", LINE1(0));
                clcd_print("Wait for...  min", LINE2(0));
                while(min)
                {
                    clcd_putch((min / 10) + '0', LINE2(11));
                    clcd_putch((min % 10) + '0', LINE2(12));
                }
                attempts_rem = 3;
                
            }
            //wrong password message
            else
            {
                clear_screen();
                clcd_print("Wrong Password", LINE1(0));
                clcd_putch(attempts_rem + '0', LINE2(0));
                clcd_print(" Attempt remain", LINE2(1));
                __delay_ms(4000);
            }
            clear_screen();
            clcd_print(" Enter Password",LINE1(0));
            i = 0;
            return_time = 5;
            clcd_write(CURSOR_POS, INST_MODE);
            clcd_write(DISP_ON_AND_CURSOR_ON, INST_MODE);
            __delay_us(100);
        }
    }
    return 0xFF;
}
//function for login menu
char login_menu(unsigned char key, unsigned char reset_flag)
{
    //change menu_pos by SW4 and SW5
    static char menu_pos;
    if(reset_flag == RESET_MENU)
    {
        menu_pos = 0;
        clear_screen();
    }
    if(key == SW4 && menu_pos <= 3)
    {
        menu_pos++;
        clear_screen();
    }
    else if(key == SW5 && menu_pos > 0)
    {
        menu_pos--;
        clear_screen();
    }
    //* move with menu_pos
    if(menu_pos < 4)
    {
        clcd_putch('*', LINE1(0));
        clcd_print(menu[menu_pos], LINE1(2));       //0 1 2 3  
        clcd_print(menu[menu_pos + 1], LINE2(2));   //1 2 3 4
    }
    else if(menu_pos == 4)
    {
        clcd_print(menu[menu_pos - 1], LINE1(2));        
        clcd_print(menu[menu_pos], LINE2(2));  
        clcd_putch('*', LINE2(0));
    }
    return menu_pos;
}
//function for view log
void view_log(unsigned char key, unsigned char reset_flag)
{
    unsigned char view[11];
    static char shift = 0;
    unsigned char addr;
    //if log is empty
    if(event_count == -1)
    {
        
        clcd_print("#  TIME    E   SP", LINE1(0));
        
        clcd_print("No Logs Available", LINE2(0));
    }
    //display logs on CLCD depend on key
    else
	{
        clcd_print("#  TIME    E   SP", LINE1(0));
        if ( key == SW4 && shift < event_count ) //sw4 to move forward
        {
            shift++;
            clear_screen() ;
        }
		else if ( key == SW5 && shift > 0 ) //sw5 to move backward
        {
			shift--;
           clear_screen() ;
        }
        //update address of eeprom
        addr = shift * 10 + 0x05;
        //extracting information from eeprom and store in view[]
        for ( int i = 0 ; i < 10 ; i++ )
		{
            view[i] = eeprom_at24c04_random_read(addr + (unsigned char) i);
		}
        clcd_write(DISP_ON_AND_CURSOR_OFF, INST_MODE);
		//printing logs on clcd one by one
		clcd_putch ( shift + '0' , LINE2(0));
		clcd_putch ( view[0] , LINE2(2));
		clcd_putch ( view[1] , LINE2(3));
		clcd_putch ( ':' , LINE2(4));
		clcd_putch ( view[2] , LINE2(5));
		clcd_putch ( view[3] , LINE2(6));
		clcd_putch ( ':' , LINE2(7));
		clcd_putch ( view[4] , LINE2(8));
		clcd_putch ( view[5] , LINE2(9));
		clcd_putch ( view[6] , LINE2(11));
		clcd_putch ( view[7] , LINE2(12));
		clcd_putch ( view[8] , LINE2(14));
		clcd_putch ( view[9] , LINE2(15));    
	}    
}
//function for clear logs
char clear_log (unsigned char reset_flag)
{
    //display message
	clcd_print( "Logs cleared",LINE1(2));
	clcd_print( "successfully", LINE2(2));
    /*clearing all the logs*/
	if ( reset_flag == RESET_CLEAR )
	{
		pos = -1;
		event_count = -1 ;
		return TASK_SUCCESS;
	}
	return TASK_FAILURE;
}

//function for download log
void download_log(void)
{
    int next = -1;
    char logs[9];
    int lpos = 0;
    unsigned char addr;
    //no logs
    if (event_count == -1)
	{
		puts("No logs avaiable");
	}
	else
	{
        //displaying all logs available
		puts("Logs :");
		putchar('\n');

		while (  next < event_count )
		{
			next++;
			lpos = (overflow)? (pos + 1) % 10 : 0;
			lpos = (lpos + next) % 10;

			for ( int i = 0 ; i < 10 ; i++ )
			{
				addr = lpos * 10 + 5 + i ;
				logs[i] = eeprom_at24c04_random_read(addr);
			}
            //printing all logs in cutecom
			putchar ( next + '0');
			putchar(' ');
			putchar ( logs[0] );
			putchar ( logs[1] );
			putchar (':');
			putchar ( logs[2] );
			putchar ( logs[3] );
			putchar (':');
			putchar ( logs[4] );
			putchar ( logs[5] );
			putchar (' ');
			putchar ( logs[6] );
			putchar ( logs[7] );
			putchar (' ');
			putchar ( logs[8] );
			putchar ( logs[9] );
			putchar ( '\n' );
			putchar ('\r');
		}
	}
}

//function for change password
char change_password(unsigned char key, char reset_pwd )
{
	static char new_pwd[9];
	static int pwd_pos = 0;
	static char i=0;

    /*logic to change password*/

	if ( reset_pwd == RESET_PASSWORD )
	{
		strncpy(new_pwd, "    ",4);
		pwd_pos = 0;
		return_time = 5;
        
	}
    
	if (return_time == 0)
		return RETURN_BACK;
    
    //first time enter new password
	if ( pwd_pos < 4 ){
		clcd_print("Enter new pwd    ",LINE1(0));}
    //second time enter new password
	else if ( pwd_pos > 3 && pwd_pos < 8 ){
		clcd_print("Re enter new pwd    ",LINE1(0));
    }
	//storing 1 and 0 depend on key pressed
    //displaying star
	switch( key)
	{
        case SW4 :
			new_pwd[pwd_pos] = '1';
			clcd_putch('*',LINE2(6+i));
			pwd_pos++;
            i++;
            return_time = 5;
            if ( pwd_pos == 4 ){
             i=0;  clear_screen();}
			break;
            
		case SW5 :
			new_pwd[pwd_pos] = '0';
			clcd_putch('*',LINE2(6+i));
			pwd_pos++;
            i++;
            return_time = 5;
            if ( pwd_pos == 4 ){
            i=0;    clear_screen();}
			break;           		
	}
    
    //if new password enter two times
    //compare both new password
	if ( pwd_pos == 8)
	{
		if ( strncmp(new_pwd, &new_pwd[4], 4) == 0 )
		{
            //if both same successfully changing password and store in eeprom
			eeprom_at24c04_str_write( 0x00, &new_pwd[4]);
			//display message
			clcd_print("Password changed",LINE1(0));
			clcd_print("successfully ",LINE2(2));
            clear_screen();
			return TASK_SUCCESS;
		}
		else
		{
            //if new password are different then fail
			clcd_print ( "Password  change" , LINE1(0));
			clcd_print("failed",LINE2(5));
			clear_screen();
			return TASK_SUCCESS;
		}
	}

	return TASK_FAILURE;
}

//function for set time
char set_time( unsigned char key ,unsigned char reset_time )
{
    /*logic to change time*/
    static unsigned int new_time[3];
	static int blink_pos ;
	static unsigned char wait , blink ;
	char dummy;
	static char done = 0;
	if ( reset_time == RESET_TIME )
	{
        get_time();
		new_time[0] = (time[0] & 0x0F ) * 10 + (time[1] & 0x0F) ;
		new_time[1] = (time[2]  & 0x0F ) * 10 + (time[3] & 0x0F) ;
		new_time[2] = (time[4] & 0x0F ) * 10 + (time[5] & 0x0F) ;
		clcd_print("  HH:MM:SS",LINE1(0));
		blink_pos = 2;
		wait = 0;
		blink = 0;
		key = ALL_RELEASED;
		done = 0;
	}

    if(done)
        return TASK_FAILURE;

	switch ( key )
	{
        //increement time value
		case SW4 :
			new_time[blink_pos]++;
			break;
        //changing field
		case SW5 :
			blink_pos = (blink_pos + 1) % 3;
			break;
		case SW6 :
            /*storing new time*/
			get_time();
			dummy = ((new_time[0] / 10 ) << 4 ) | new_time[0] % 10 ;
			clock_reg[0] = (clock_reg[0] & 0xc0) | dummy ;
			write_ds1307(HOUR_ADDR, clock_reg[0] );
			dummy = ((new_time[1] / 10 ) << 4 ) | new_time[1] % 10 ;
			clock_reg[1] = (clock_reg[1] & 0x80) | dummy;
			write_ds1307(MIN_ADDR, clock_reg[1] );
			dummy = ((new_time[2] / 10 ) << 4 ) | new_time[2] % 10 ;
			clock_reg[2] = (clock_reg[2] & 0x80) | dummy;
			write_ds1307(SEC_ADDR, clock_reg[2] );
			clear_screen();
			clcd_print("Time changed",LINE1(2));
			clcd_print("Successfully",LINE2(2));
            __delay_ms(2000);
			done = 1;
			return  TASK_SUCCESS;
    }
    //set start and finish limit 
	if( new_time[0]  > 23 )
		new_time[0] = 0;
	if ( new_time[1] > 59 )
		new_time[1] = 0;
	if ( new_time[2] > 59 )
		new_time[2] = 0;
    
    //display hour minute and second value on clcd
    //blinking
	if ( wait ++ == 100 )
	{
		wait = 0;
		blink = !blink;
		clcd_putch( new_time[0] / 10 + '0', LINE2(2));
		clcd_putch( new_time[0] % 10 + '0' , LINE2(3));
		clcd_putch( ':', LINE2(4));
		clcd_putch( new_time[1] / 10 + '0', LINE2(5));
		clcd_putch( new_time[1] % 10 + '0', LINE2(6));
		clcd_putch( ':', LINE2(7));
		clcd_putch( new_time[2] / 10 + '0' , LINE2(8));
		clcd_putch( new_time[2] % 10 + '0', LINE2(9));
        
        //logic to blink at the current pos
		if ( blink)
		{
			switch( blink_pos )
			{
				case 0:
					clcd_print("  ",LINE2(2));
					break;
				case 1:
					clcd_print("  ",LINE2(5));
					break;
				case 2:
					clcd_print("  ",LINE2(8));
					break;
			}
		}
	}
	return TASK_FAILURE;
}