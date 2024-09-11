/*Implmentation for Pipes was obtained from Lecture 5 Process API on Blackboard. Details for implementation
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

int READ_END = 0; 
int WRITE_END = 1;

int main(int argc, char *argv[]){
    //Turn off buffering
    setbuf(stdout, NULL);

    int fd[2];
    if(pipe(fd) == -1){
        perror("pipe() failed");
        return errno;
    }

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
        /* Calculating the absolute time in seconds from Jan 1, 1970 */
        long double total_start_time = start_seconds + (start_microseconds / 1000000.0);  

        char time_message[32];
        sprintf(time_message, "%.05Lf", total_start_time);
        close(fd[READ_END]); /* Close unused end */
        write(fd[WRITE_END], time_message, 32); /* Write */
        close(fd[WRITE_END]); /* Close pipe */

        /* Exec */
        execvp(argv[1], &argv[1]);
    }
    else { /* parent process */
    /* parent will wait for the child to complete */
    /* After child completes, define end time struct, retrieve time, and print child complete*/
        wait(NULL);
        char time_message[32];
        close(fd[WRITE_END]); /* Close unused end of pipe */
        read(fd[READ_END], time_message, 32); /* Read from pipe */
        close(fd[WRITE_END]);

        long double total_start_time = atof(time_message);

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