/* This program is an exercise in implementation of multithreaded programming using the pthread library. It uses Monte Carlo Sampling to estimate the value
of pi and calls the sampling function as its own thread. This implementation uses TWO threads, also demonstrating a race condition. */
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int points_inside;
int total_points;

void *generate_points(void *num_points);
double calculate(int total, int inside);

int main(int argc, char *argv[]){
    /* Thread identifier and thread attributes */
    pthread_t tid;
    pthread_attr_t attr;

    /* Set the default attributes of the threads */
    pthread_attr_init(&attr);
    /* Create the TWO threads */
    pthread_create(&tid, &attr, generate_points, argv[1]);
    pthread_create(&tid, &attr, generate_points, argv[1]);
    /* Wait for the threads to exit */
    pthread_join(tid, NULL);
    
    /* Calculating the value of pi based on points inside circle and printing the calculated value */
    double pi = calculate(total_points, points_inside);
    printf("%2.5f\n", pi);
    return 0;
}

void *generate_points(void* num_points){
    /* Converting the command line arg to an integer and generating a random seed for the rng */
    total_points = atoi(num_points);
    srand(time(NULL));
    
    for(int i = 0; i < total_points; i++){
        /* Generating a random number from 0 to 1 for x and y */
        double x = (double)rand() / (double)RAND_MAX;
        double y = (double)rand() / (double)RAND_MAX;

        if(sqrt(pow(x, 2) + pow(y, 2)) < 1){
            points_inside++;
        }
    }
    pthread_exit(0);
}

double calculate(int total, int inside){
    return (double)4 * (double)inside / ((double)total * 2);
}