#ifndef __EL_PORT_POSIX_H__
#define __EL_PORT_POSIX_H__
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

typedef sem_t el_sem_t;

typedef pthread_mutex_t el_mutex_t;

typedef pthread_spinlock_t el_spinlock_t;

typedef pthread_t el_thread_t;

#endif