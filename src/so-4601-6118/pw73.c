/* SO 4601-6118 - C90, C99 */
#include <stdio.h>
#include <stdbool.h>

typedef struct user
{
    bool empty;
    int lineNumber;
    char *errMessage;
    union
    {
        struct
        {
            char *username;
            char *password;
            char *uid;
            char *gid;
            char *gecos;
            char *dir;
            char *shell;
        } f;
        char *field[7];
    } u;
} user;

typedef enum {username, password, uid, gid, gecos, dir, shell} userValue;

static void parseHelper(user *u, userValue enumParam, char *value)
{
    u->u.field[enumParam] = value;
}

int main(void)
{
    user u;
    u.empty = false;
    u.lineNumber = 1;
    u.errMessage = "no error";
    parseHelper(&u, password, "secret");
    parseHelper(&u, username, "me");
    parseHelper(&u, uid, "0");
    parseHelper(&u, gid, "1");
    parseHelper(&u, gecos, "Yours Truly");
    parseHelper(&u, dir, "/home/me");
    parseHelper(&u, shell, "/bin/sea");

    printf("%s:%s:%s:%s:%s:%s:%s\n", u.u.f.username, u.u.f.password,
           u.u.f.uid, u.u.f.gid, u.u.f.gecos, u.u.f.dir, u.u.f.shell);
    return 0;
}
