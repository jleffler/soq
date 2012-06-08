/*
** SO 10938882
** Using tcflush() to clear unread input from a tty
*/

#include <stdio.h>
#include <unistd.h>
#include <termios.h>

int main(void)
{
    char buffer[20] = "";

    read(0, buffer, 1);
    printf("%c\n", buffer[0]);
    tcflush(0, TCIFLUSH);
    read(0, buffer, 1);
    printf("%c\n", buffer[0]);
    tcflush(0, TCIFLUSH);
    return 0;
}
