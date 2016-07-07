/*
@(#)File:           $RCSfile$
@(#)Version:        $Revision$
@(#)Last changed:   $Date$
@(#)Purpose:        Create and attach to a shared memory segment
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2015
@(#)Product:        :PRODUCT:
*/

/*TABSTOP=4*/

#include "posixver.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include "so-stderr.h"

enum { DEFAULT_SHM_SIZE = 65536 };
enum { DEFAULT_FTOK_ID = 0 };
static const char default_filename[] = "/etc/passwd";

static const char usestr[] = "[-adx][-f file][-s size][-i id]";
static const char optstr[] = "adf:s:x";
//static const char usestr[] = "[-adhxV][-f file][-s size][-i id]";
//static const char optstr[] = "adf:hs:xV";
//static const char hlpstr[] =
//    "  -a       Attach only (segment must already exist)\n"
//    "  -d       Delete the shared memory chunk\n"
//    "  -f file  File name to be used to create shared memory ID\n"
//    "  -h       Print this help and exit\n"
//    "  -i id    Integer ID used with ftok()\n"
//    "  -s size  How big the shared memory chunk should be\n"
//    "  -x       Fail if shared memory already exists\n"
//    "  -V       Print version information and exit\n"
//    ;

//#ifndef lint
///* Prevent over-aggressive optimizers from eliminating ID string */
//extern const char jlss_id_shm_master_c[];
//const char jlss_id_shm_master_c[] = "@(#)$Id$";
//#endif /* lint */

int main(int argc, char **argv)
{
    int aflag = 0;
    int xflag = 0;
    int dflag = 0;
    int id = DEFAULT_FTOK_ID;
    size_t size = DEFAULT_SHM_SIZE;
    const char *file = default_filename;
    int opt;

    err_setarg0(argv[0]);
    while ((opt = getopt(argc, argv, optstr)) != -1)
    {
        switch (opt)
        {
        case 'a':
            aflag = 1;
            break;
        case 'd':
            dflag = 1;
            break;
        case 'f':
            file = optarg;
            break;
        //case 'h':
        //    err_help(usestr, hlpstr);
        //    /*NOTREACHED*/
        case 'i':
            id = atoi(optarg);
            break;
        case 's':
            size = strtoull(optarg, 0, 0);
            if (size == 0)
                err_error("Invalid size (%s) evaluates to zero\n", optarg);
            break;
        case 'x':
            xflag = 1;
            break;
        //case 'V':
        //    err_version("SHM-MASTER", &"@(#)$Revision$ ($Date$)"[4]);
        //    /*NOTREACHED*/
        default:
            err_usage(usestr);
            /*NOTREACHED*/
        }
    }

    if (aflag + dflag + xflag > 1)
        err_error("%d of 3 mutually exclusive options -a, -d and -x specified\n", aflag + dflag + xflag);

    printf("ID: %d, File: %s\n", id, file);
    key_t key = ftok(file, id);
    printf("Key: 0x%.8" PRIX64 "\n", (uint64_t)key);
    int shmflg = S_IRUSR | S_IWUSR;
    if (!aflag && !dflag)
        shmflg |= IPC_CREAT;
    if (xflag)
        shmflg |= IPC_EXCL;

    int shmid = shmget(key, size, shmflg);
    if (shmid < 0)
        err_syserr("Failed to get shared memory ID: ");
    printf("ShmID: %d\n", shmid);

    if (dflag)
    {
        struct shmid_ds buf;
        int rc = shmctl(shmid, IPC_RMID, &buf);
        if (rc < 0)
            err_syserr("Failed to delete shared memory: ");
        printf("Shared memory removed\n");
    }
    else
    {
        void *space = shmat(shmid, 0, 0);
        if (space == (void *)-1)
            err_syserr("Failed to attach to shared memory: ");
        printf("Shared memory allocated at 0x%" PRIXPTR "\n", (uintptr_t)space);
        memset(space, '\0', size);
        int rc = shmdt(space);
        if (rc != 0)
            err_syserr("Failed to detach from shared memory: ");
        printf("Detached from shared memory\n");
    }

    return 0;
}

