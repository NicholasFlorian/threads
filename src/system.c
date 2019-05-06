
/**
 * @file system.c
 * @author Nicholas Florian
 * @date April 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "system.h"


// for mutual exlusion
pthread_mutex_t lock;       // mutex
int product_red;            // global variable for testing mutual exclusion


int main() {

    // variables
    int amount;
    pthread_t* threads;


    // prompt user
    printf("system.c :: by Nicholas Florian\n");
    printf("\tShows the functionality of thread theory...\n");
    printf("\tEach Thread has static variable which can show the damaging effects of poor management.\n");
    printf("\t\tThreads with \'0\' were run successfully:\n");
    printf("\t\tWhite Threads are using JOINS.\n");
    printf("\t\t\x1b[31mRed\x1b[0m Threads are using MUTEX and global variables.\n");
    printf("\t\t\x1b[32mGreen\x1b[0m Threads are using nothing to manage themselves.\n\n\n");

    // create our lock
    if (pthread_mutex_init(&lock, NULL) != 0){

        // exit with error
        printf("Lock Failed. Quiting...\n");
        return 1;
    }


    // create our threads
    amount = 20;

    threads = malloc(sizeof(pthread_t) * amount);
    if(threads == NULL){

        // exit with error
        printf("Memory Failed. Quiting...\n");
        return 1;
    }


    // run each of our threads
    for(int i = 0; i < amount; i++){

        // variables
        int error;
        int error_red;
        int error_green;    // all of these track errors

        int index; // this variable solves pointer issues with &i, by creating a new int new a smaller scope


        // assign false to start, incase other functions want to be removed
        error = 1;
        error_red = 1;
        error_green = 1;

        // assign index
        index = i;


        /*  Remove any of these functions, their joins, or their mutex locks
         *  to see their desired effect...
         *
         *  Using 'i' instead of index can produce bugs as well...
         */

        // thread with join *remove join for some fun!
        error = pthread_create(&threads[i], NULL, &thread_func, &index);
        pthread_join(threads[i], NULL);

        // thread with mutex

        error_red = pthread_create(&threads[i], NULL, &thread_func_red, &index);

        // thread with no join
        error_green = pthread_create(&threads[i], NULL, &thread_func_green, &index);


        // print data
        printf("\x1b[36m<<ERROR: %d>> <<ERROR_RED: %d>> <<ERROR_GREEN: %d>>\x1b[0m\n",
            error,
            error_red,
            error_green);
    }


    // delete our lock
    pthread_mutex_destroy(&lock);

    // free our threads
    free(threads);


    return 0;
}

void* thread_func(void *arg) {

    // static variables
    static int order = 0;


    // variables
    int *thread_id;
    int product;


    // assign
    order++;
    thread_id   = (int*) arg;
    product     = *thread_id - order;

    // prompt
    printf("Running Thread :: %d;\n", *thread_id);
    printf("\t(Thread: %d),\tOrder: %d,\tproduct: %d;\n",
        *thread_id,
        order,
        product);
    printf("\tEnd of Thread :: %d;\n", *thread_id);


    return NULL;
}

void* thread_func_red(void *arg) {


    // start lock after static variable is declared once (or not?)
    pthread_mutex_lock(&lock);

    // static variables
    static int order = 0;


    // variables
    int thread_id; // notice how this thread is not an int, should have copyied the pointers value and not the pointer itself.


    // assign
    order++;
    thread_id   = * (int *) arg;
    product_red = thread_id - order;

    // end lock after our global variable is complete
    pthread_mutex_unlock(&lock);

    // prompt
    printf("\x1b[31mRunning Thread :: %d;\x1b[0m\n", thread_id);
    printf("\t\x1b[31m(Thread: %d),\tOrder: %d,\tproduct: %d;\x1b[0m\n",
        thread_id,
        order,
        product_red);
    printf("\t\x1b[31mEnd of Thread :: %d;\x1b[0m\n", thread_id);


    // end lock after prompt
    //pthread_mutex_unlock(&lock);

    return NULL;
}

void* thread_func_green(void *arg) {

    // static variables
    static int order = 0;


    // variables
    int *thread_id;
    int product;


    // assign
    order++;
    thread_id   = (int*) arg;
    product     = *thread_id - order;

    // prompt
    printf("\x1b[32mRunning Thread :: %d;\x1b[0m\n", *thread_id);
    printf("\t\x1b[32m(Thread: %d),\tOrder: %d,\tproduct: %d;\x1b[0m\n",
        *thread_id,
        order,
        product);
    printf("\t\x1b[32mEnd of Thread :: %d;\x1b[0m\n", *thread_id);


    return NULL;
}
