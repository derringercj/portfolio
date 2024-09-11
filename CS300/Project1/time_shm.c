/*Implmentation for Shared Memory was obtained from Lecture 5 Process API on Blackboard. Details for implementation
on the timeval struct and necessary function and features was obtained from the C reference website cplusplus.com/reference */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
 
int main(int argc, char *argv[]){
    //Turn off buffering
    setbuf(stdout, NULL);

    //Declaring process identifier variable and timeval struct for start time
    pid_t pid;
 
    /* fork a child process */
    pid = fork();
 
    if (pid < 0) { /* error occurred */
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    else if (pid == 0) { /* child process */
        /* Creating timeval struct, retrieving time of day */
        struct timeval start_time;
        gettimeofday(&start_time, 0);
        long double start_seconds = start_time.tv_sec;
        long double start_microseconds = start_time.tv_usec;

        /* Setting a predefined size and name for our shared memory and creating pointer to shared memory object */
        int SIZE = 4096;
        char *name = "/SharedMem";
        int shm_fd;
        void *ptr;
        
        /* Creating shared memory file descriptor, then creating the shared memory object with our predefined name and setting its size */
        shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
        if(shm_fd == -1){
            printf("Shared Memory Failed\n");
            exit(-1);
        }
        ftruncate(shm_fd, SIZE);

        /* Memory mapping the shm object */
        ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
        if(ptr == MAP_FAILED){
            printf("Map Failed\n");
            return -1;
        }
        /* Calculating the absolute time in seconds from Jan 1, 1970 */
        long double total_start_time = start_seconds + (start_microseconds / 1000000.0);

        /* Writing to shared memory*/
        sprintf(ptr, "%.05Lf", total_start_time);    

        /* Exec */
        execvp(argv[1], &argv[1]);
    }
    else { /* parent process */
    /* parent will wait for the child to complete */
    /* After child completes, define end time struct, retrieve time, and print child complete*/
        wait(NULL);
        /* Setting size and name, as well as defining proper variables */
        int SIZE = 4096;
        char *name = "/SharedMem";
        int shm_fd;
        void *ptr;
        /* Creating shared memory file descriptor, then creating the shared memory object with our predefined name and setting its size */
        shm_fd = shm_open(name, O_RDONLY, 0666);
        /* Error checking */
        if(shm_fd == -1){
            printf("Shared Memory Failed\n");
            exit(-1);
        }
        /* Mapping shared memory */
        ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

        /* Error checking */
        if(ptr == MAP_FAILED){
            printf("Map failed\n");
            exit(-1);
        }

        /* Reading from shared memory */
        long double total_start_time = atof(ptr);

        /* Verifying unlink */
        if(shm_unlink(name) == -1){
            printf("Error removing %s\n", name);
            exit(-1);
        }

        /* Retrieving end time */
        struct timeval end_time;
        gettimeofday(&end_time, 0);
        long double end_seconds = end_time.tv_sec;
        long double end_microseconds = end_time.tv_usec;

        /* Calculating time elapsed and printing */
        long double total_end_time = end_seconds + (end_microseconds / 1000000.0);
        long double time_elapsed = total_end_time - total_start_time;
        printf("Time Elapsed: %Lf\n", time_elapsed);
    }
 
    return 0;
}