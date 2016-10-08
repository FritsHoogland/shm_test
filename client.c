#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define SHMSZ     2

main()
{
    /*
     * variables
     */
    int shmid;
    key_t key;
    char *shm, *s, p;

    /*
     * Set the segment key to "666".
     */
    key = 666;

    /*
     * Get the shared memory id by using the key value.
     */
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    /*
     * Attach the segment the process' address space.
     */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    /*
     * Assign the shared memory id pointer to s.
     */
    s = shm;
    
    printf("client started. ^C to quit.\n");

    while( 1 ){
       printf("waiting for enter\n");
       getchar();
       if( p != *s ) {
          printf("keystroke: %c\n", *s);
          p = *s;
          }
    }

    exit(0);
}
