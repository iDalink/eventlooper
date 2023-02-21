#include "el_port.h"
#include <time.h>
#include <sys/time.h>
#include <unistd.h>


void *el_mem_malloc(int size)
{
    return malloc(size);
}

void *el_mem_realloc(void *ptr, int size)
{
    return realloc(ptr, size);
}

void  el_mem_free(void *ptr)
{
    free(ptr);
}

int el_sem_create(el_sem_t *sem)
{
    return sem_init(sem, 0, 0);
}

int el_sem_post(el_sem_t *sem)
{
    return sem_post(sem);
}

int el_sem_wait(el_sem_t *sem)
{
    return sem_wait(sem);
}

int el_sem_trywait(el_sem_t *sem)
{
    return sem_trywait(sem);
}

int el_sem_destroy(el_sem_t *sem)
{
    sem_destroy(sem);
}

int el_mutex_create(el_mutex_t *mutex)
{
    return pthread_mutex_init(mutex, NULL);
}

int el_mutex_lock(el_mutex_t *mutex)
{
    return pthread_mutex_lock(mutex);
}

int el_mutex_trylock(el_mutex_t *mutex)
{
    return pthread_mutex_trylock(mutex);
}

int el_mutex_unlock(el_mutex_t *mutex)
{
    return pthread_mutex_unlock(mutex);
}

int el_mutex_destroy(el_mutex_t *mutex)
{
    return pthread_mutex_destroy(mutex);
}

int el_spin_create(el_spinlock_t *spin)
{
    return pthread_spin_init(spin, 0);
}

int el_spin_lock(el_spinlock_t *spin)
{
    return pthread_spin_lock(spin);
}

int el_spin_trylock(el_spinlock_t *spin)
{
    return pthread_spin_unlock(spin);
}

int el_spin_unlock(el_spinlock_t *spin)
{
    return pthread_spin_unlock(spin);
}

int el_spin_destroy(el_spinlock_t *spin)
{
    return pthread_spin_destroy(spin);
}

long long el_ticks_get(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    long long time = (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
    return time;
}

void el_sleep_ms(int ms)
{
    usleep(ms * 1000);
}

int el_thread_create(el_thread_t *thread, void *attr, int prio, 
                     void *(* fun)(void *), void *param)
{
    return pthread_create(thread, attr, fun, param);
}
