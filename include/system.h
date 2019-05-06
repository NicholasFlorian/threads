/**
 * @file system.h
 * @author Nicholas Florian
 * @date April 2019
 */


#ifndef _SYSTEM_API_
#define _SYSTEM_API_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "system.h"


// standard thread function (Post ~ Join this variable)
void* thread_func(void *arg);

// standard thread for testing Mutex (pre and post ~ make sure lock is handled)
void* thread_func_red(void *arg);

// standard thread function (Post ~ Unjoined chaos)
void* thread_func_green(void *arg);

#endif
