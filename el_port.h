#ifndef __EL_PORT_H__
#define __EL_PORT_H__
#include "el_port_posix.h"

void *el_mem_malloc(int size);
void *el_mem_malloc_from_spiram(int size);
void *el_mem_realloc(void *ptr, int size);
void *el_mem_realloc_from_spiram(void *ptr, int size);
void  el_mem_free(void *ptr);

//typedef xxx el_sem_t;
int el_sem_create(el_sem_t      *sem);
int el_sem_post(el_sem_t      *sem);
int el_sem_wait(el_sem_t      *sem);
int el_sem_trywait(el_sem_t   *sem);
int el_sem_destroy(el_sem_t    *sem);

//typedef xxx el_mutex_t;
int el_mutex_create(el_mutex_t      *mutex);
int el_mutex_lock(el_mutex_t      *mutex);
int el_mutex_trylock(el_mutex_t   *mutex);
int el_mutex_unlock(el_mutex_t    *mutex);
int el_mutex_destroy(el_mutex_t    *mutex);

//typedef xxx el_spinlock_t;
int el_spin_create(el_spinlock_t    *spin);
int el_spin_lock(el_spinlock_t    *spin);
int el_spin_trylock(el_spinlock_t *spin);
int el_spin_unlock(el_spinlock_t  *spin);
int el_spin_destroy(el_spinlock_t  *spin);

long long el_ticks_get(void);
void el_sleep_ms(int ms);

//typedef xxx el_thread_t;

#define EL_THREAD_PRIO_HIGH 0
#define EL_THREAD_PRIO_MID  1
#define EL_THREAD_PRIO_LOW  2
int el_thread_create(el_thread_t *thread, void *attr, int prio, 
                     void *(* fun)(void *), void *param);

#endif
