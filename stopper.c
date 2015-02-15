/* SO 7778268 */
/* http://www.wienand.org/junkcode/linux/stopper.c */

/* very simple ptrace example to stop a process before it exits.  This
 * allows us to inspect /proc/pid/ values, for example.
 * (C) 2007 Ian Wienand <ianw@ieee.org>
 * Public Domain
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <sys/wait.h>

#include <sys/ptrace.h>

/* for some reason glibc doesn't yet include the PTRACE_OPTIONS,
 * clagged from kernel */

/* options set using PTRACE_SETOPTIONS */
#define PTRACE_O_TRACESYSGOOD   0x00000001
#define PTRACE_O_TRACEFORK      0x00000002
#define PTRACE_O_TRACEVFORK     0x00000004
#define PTRACE_O_TRACECLONE     0x00000008
#define PTRACE_O_TRACEEXEC      0x00000010
#define PTRACE_O_TRACEVFORKDONE 0x00000020
#define PTRACE_O_TRACEEXIT      0x00000040

#define PTRACE_O_MASK           0x0000007f

/* Wait extended result codes for the above trace options.  */
#define PTRACE_EVENT_FORK       1
#define PTRACE_EVENT_VFORK      2
#define PTRACE_EVENT_CLONE      3
#define PTRACE_EVENT_EXEC       4
#define PTRACE_EVENT_VFORK_DONE 5
#define PTRACE_EVENT_EXIT       6

pid_t pid;

void sigint_handler(int signum)
{
	/* let the child die */
	if (ptrace(PTRACE_CONT, pid, 0, 0)) {
		perror("stopper: ptrace(PTRACE_CONT, ...)");
		exit(1);
	}
	exit(0);
}

/* wait for the pid to exit */
void wait_for_exit(void)
{
	int status;
	while (1) {
		/* wait for signal from child */
		waitpid(pid, &status, 0);

		/* any signal stops the child, so check that
		   the incoming signal is a SIGTRAP and the
		   event_exit flag is set */
		if ( (WSTOPSIG(status) == SIGTRAP) &&
		     (status & (PTRACE_EVENT_EXIT << 8)))
			break;

		/* if not, pass the original signal onto the child */
		if (ptrace(PTRACE_CONT, pid, 0, WSTOPSIG(status))) {
			perror("stopper: ptrace(PTRACE_CONT, ...)");
			exit(1);
		}
	}

	/* at this point, register the clean-up signal handler
	 * (previously we just want a normal exit */
	signal(SIGINT, sigint_handler);

	printf("\n-----------------------------------------------------\n");
	printf("\n\t  STOPPED PID %d\n", pid);
	printf("\t ctrl-c to continue\n");
	printf("\n-----------------------------------------------------\n");
	while (1)
		sleep(1000);
}

char *usage = "Usage: stopper [ [-p pid] | command ]";

int main(int argc, char *argv[])
{
	extern char *optarg;
	extern int optind, opterr, optopt;
	char c;
	bool attaching = false;

	while ((c = getopt(argc, argv,
			   "+p:")) != -1) {
		switch (c) {

		case 'p':
			pid = atoi(optarg);
			attaching = true;
			break;
		default:
			printf("%s", usage);
			exit(1);
		}
	}

	if (optind == argc && !attaching) {
		printf("%s\n", usage);
		exit(1);
	}

	if (!attaching) {
		/* find the file to exec, borrowed from strace */
		struct stat statbuf;
		char *filename;
		char pathname[MAXPATHLEN];

		filename = argv[optind];
		if (strchr(filename, '/')) {
			if (strlen(filename) > sizeof(pathname) - 1) {
				errno = ENAMETOOLONG;
				perror("stopper: exec failed");
				exit(1);
			}
			strcpy(pathname, filename);
		}
		else {
			char *path;
			int m, n, len;

			for (path = getenv("PATH"); path && *path; path += m) {
				if (strchr(path, ':')) {
					n = strchr(path, ':') - path;
					m = n + 1;
				}
				else
					m = n = strlen(path);
				if (n == 0) {
					getcwd(pathname, MAXPATHLEN);
					len = strlen(pathname);
				}
				else if (n > sizeof pathname - 1)
					continue;
				else {
                                        strncpy(pathname, path, n);
                                        len = n;
				}
				if (len && pathname[len - 1] != '/')
					pathname[len++] = '/';
				strcpy(pathname + len, filename);
				if (stat(pathname, &statbuf) == 0 &&
				    /* Accept only regular files
				       with some execute bits set.
				       XXX not perfect, might still fail */
				    S_ISREG(statbuf.st_mode) &&
				    (statbuf.st_mode & 0111))
					break;
			}
		}

		if (stat(pathname, &statbuf) < 0) {
			fprintf(stderr, "%s: %s: command not found\n",
				argv[0], filename);
			exit(1);
		}

		switch (pid = fork()) {
		case -1:
			perror("stopper: fork");
			exit(1);
			break;
		case 0:
			if (ptrace(PTRACE_TRACEME, 0, (char *)1, 0) < 0) {
				perror("stopper: ptrace(PTRACE_TRACEME, ...)");
				return -1;
			}
			execv(pathname, &argv[optind]);
			perror("stopper: execv");
			_exit(1);

		default:
			/* wait for first signal, which is from child when it execs */
			wait(NULL);

			/* set option to tell us when the signal exits */
			if (ptrace(PTRACE_SETOPTIONS, pid, 0, PTRACE_O_TRACEEXIT)) {
				perror("stopper: ptrace(PTRACE_SETOPTIONS, ...)");
				return -1;
			}

			/* allow child to continue */
			if (ptrace(PTRACE_CONT, pid, 0, (void*)0)) {
				perror("stopper: ptrace(PTRACE_CONT, ...)");
				return -1;
			}

			wait_for_exit();
		}

	} else {
		/* we are attaching to a running PID */

		if (ptrace(PTRACE_ATTACH, pid, 0, 0)) {
			perror("stopper: can not attach to process");
			return -1;
		}

		/* set option to tell us when the signal exits */
		if (ptrace(PTRACE_SETOPTIONS, pid, 0, PTRACE_O_TRACEEXIT)) {
			perror("stopper: ptrace(PTRACE_SETOPTIONS, ...)");
			return -1;
		}

		wait_for_exit();
	}

	/* shouldn't get here */
	exit(1);
}

