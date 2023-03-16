 /*
 * Name : Suraj Roy
 * Date : 15/10/2022
 * Description : Car black box
 */

#ifndef CAR_BB_H
#define	CAR_BB_H

void display_dashboard(unsigned char event[], unsigned char speed);
void log_car_event(char event[],unsigned char speed);
void clear_screen(void);
unsigned char login(unsigned char key, unsigned char reset_flag);
char login_menu(unsigned char key, unsigned char reset_flag);
void view_log(unsigned char key, unsigned char reset_flag);
char clear_log (unsigned char reset_flag);
void download_log(void);
char change_password(unsigned char key, char reset_pwd );
char set_time( unsigned char key ,unsigned char reset_time );


#endif	/* CAR_BB_H */

