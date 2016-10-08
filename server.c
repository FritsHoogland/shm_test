#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define SHMSZ     2

main()
{
    char c;
    int shmid;
    key_t key;
    char *shm, *s;

    /*
     * The shared memory segment is named "666".
     */
    key = 666;

    /*
     * Create the segment.
     */
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    /*
     * Attach the segment to the address space.
     */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    /*
     * Now put some things into the memory for the
     * other process to read.
     */
    s = shm;
    c = 'a';
    printf("Type a letter. q quits.\n");
    while ( c != 'q' ) {
        *s = c;
        scanf("%c%*c", &c);
    }
    
    exit(0);
}
