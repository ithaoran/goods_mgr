#include <stdio.h>
#include <termios.h>


void disable()
{
    struct termios init_setting;
    tcgetattr(0, &init_setting);
    init_setting.c_lflag &= ~ECHO;      //关闭终端回显
    tcsetattr(0, TCSANOW, &init_setting);
}



void enable()
{
    struct termios init_setting;
    tcgetattr(0, &init_setting);
    init_setting.c_lflag |= ECHO;      //打开终端回显
    tcsetattr(0, TCSANOW, &init_setting);
}