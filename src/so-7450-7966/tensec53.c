/* SO 7450-7966 */
#include <ctype.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#undef sigemptyset      /* MacOS has a stupid macro that triggers -Wunused-value */

static struct termios sane;

static void stty_sane(void)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &sane);
}

static void stty_raw(void)
{
    tcgetattr(STDIN_FILENO, &sane);
    struct termios copy = sane;
    copy.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &copy);
}

static volatile sig_atomic_t alarm_recvd = 0;

static void alarm_handler(int signum)
{
    signal(signum, SIG_IGN);
    alarm_recvd = 1;
}

static void other_handler(int signum)
{
    signal(signum, SIG_IGN);
    stty_sane();
    exit(128 + signum);
}

static int getch(void)
{
    char c;
    if (read(STDIN_FILENO, &c, 1) == 1)
        return (unsigned char)c;
    return EOF;
}

static void set_handler(int signum, void (*handler)(int signum))
{
    struct sigaction sa = { 0 };
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;    /* No SA_RESTART! */
    if (sigaction(signum, &sa, NULL) != 0)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
}

static void dump_string(const char *tag, const char *buffer)
{
    printf("\n%s [", tag);
    int c;
    while ((c = (unsigned char)*buffer++) != '\0')
    {
        if (isprint(c) || isspace(c))
            putchar(c);
        else
            printf("\\x%.2X", c);
    }
    printf("]\n");
}

int main(void)
{
    char buffer[2048];

    stty_raw();
    atexit(stty_sane);
    set_handler(SIGALRM, alarm_handler);
    set_handler(SIGHUP, other_handler);
    set_handler(SIGINT, other_handler);
    set_handler(SIGQUIT, other_handler);
    set_handler(SIGPIPE, other_handler);
    set_handler(SIGTERM, other_handler);
    alarm(10);

    size_t i = 0;
    int c;
    while (i < sizeof(buffer) - 1 && !alarm_recvd && (c = getch()) != EOF)
    {
        if (c == sane.c_cc[VEOF])
            break;
        if (c == sane.c_cc[VERASE])
        {
            if (i > 0)
                i--;
        }
        else
            buffer[i++] = c;
    }
    buffer[i] = '\0';

    dump_string("Data", buffer);
    return 0;
}
