/* SO 4408-7031 */
#include "posixver.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct pipe_rw
{
   pid_t cpid;
   int pipe_r[2];
   int pipe_w[2];
} RWPIPE;

static char *get_user_input(void)
{
   char buf[128];
   char *input;
   char ch;
   size_t len = 0;

   while((ch = fgetc(stdin)) != '\n' && ch != EOF && len < sizeof(buf) - 2)
      buf[len++] = ch;
   buf[len++] = '\n';
   buf[len] = '\0';

   input = malloc(sizeof(char) * (len + 1));
   strncpy(input, buf, (len + 1));
   printf("Got: [%s]\n", input);
   return input;
}

static int pclose_rw(RWPIPE *rwp)
{
   int status, ret = 0;

   if (rwp)
   {
      if (rwp->cpid > 0)
      {
         kill(rwp->cpid, SIGTERM);

         do {
            ret = waitpid(rwp->cpid, &status, WUNTRACED|WCONTINUED);
         } while (!WIFEXITED(status) && !WIFSIGNALED(status));
      }

      close(rwp->pipe_r[0]);
      close(rwp->pipe_w[1]);
      free(rwp);
   }

   return ret;
}

static RWPIPE *popen_rw(const char *command)
{
   RWPIPE *rwp = (RWPIPE *)malloc(sizeof(*rwp));
   if (rwp == NULL)
      return NULL;

   memset(rwp, 0x00, sizeof(*rwp));
   if (pipe(rwp->pipe_r) != 0 || pipe(rwp->pipe_w) != 0)
   {
      free(rwp);
      return NULL;
   }

   rwp->cpid = fork();
   if (rwp->cpid == -1)
   {
      free(rwp);
      return NULL;
   }

   if (rwp->cpid == 0)
   {
      dup2(rwp->pipe_w[0], STDIN_FILENO);
      dup2(rwp->pipe_r[1], STDOUT_FILENO);

      close(rwp->pipe_r[0]);
      close(rwp->pipe_r[1]);
      close(rwp->pipe_w[0]);
      close(rwp->pipe_w[1]);

      execl(command, command, NULL);
      fprintf(stderr, "Error: fail to exec command '%s'.\n", command);
      exit (1);
   }
   else
   {
      close(rwp->pipe_r[1]);
      close(rwp->pipe_w[0]);
   }

   return rwp;
}

static ssize_t read_p(RWPIPE *rwp, void *buf, size_t count)
{
   return read(rwp->pipe_r[0], buf, count);
}

static ssize_t write_p(RWPIPE *rwp, const void *buf, size_t count)
{
   return write(rwp->pipe_w[1], buf, count);
}

int main(void)
{
   char rbuf[BUFSIZ];
   int ret, len;
   char *string;

   signal(SIGPIPE, SIG_IGN);

   RWPIPE *rwp = popen_rw("./read_write");
   if (rwp == NULL)
   {
      printf("Error: fail to open command ..\n");
      return EXIT_FAILURE;
   }

   while (1)
   {
      memset(rbuf, 0x00, sizeof(rbuf));
      if (read_p(rwp, rbuf, sizeof(rbuf)) <= 0)
      {
         printf("No more input..\n");
         break;
      }
      printf("From child: [%s]\n", rbuf);

      string = get_user_input();
      len = strlen(string);
      printf("Length %d: [%s]\n", len, string);
      ret = write_p(rwp, string, len);
      if (ret != len)
      {
         fprintf(stderr, "Write %d bytes (expected %d) ..\n", ret, len);
         break;
      }
      printf("end cycle\n");
   }
   printf("End of loop\n");
   pclose_rw(rwp);

   return EXIT_SUCCESS;
}
