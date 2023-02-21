#include "el_port_esp32.h"
#include "esp_heap_caps.h"

void *el_mem_malloc(int size)
{
    return malloc(size);
}

void *el_mem_malloc_from_spiram(int size)
{
    return heap_caps_malloc(size, MALLOC_CAP_SPIRAM);
}

void *el_mem_realloc(void *ptr, int size)
{
    return realloc(ptr, size);
}

void *el_mem_realloc_from_spiram(void *ptr, int size)
{
    return heap_caps_realloc(ptr, size, MALLOC_CAP_SPIRAM);
}

void  el_mem_free(void *ptr)
{
    free(ptr);
}

int el_sem_create(el_sem_t *sem)
{
    *sem = xSemaphoreCreateCounting(10, 0);
    if (*sem)
        return 0;
    return -1;
}

int el_sem_post(el_sem_t *sem)
{
    xSemaphoreGive(*sem);
    return 0;
}

int el_sem_wait(el_sem_t *sem)
{
    xSemaphoreTake(*sem, portMAX_DELAY);
    return 0;
}

int el_sem_trywait(el_sem_t *sem)
{
    return !(xSemaphoreTake(*sem, 0) == pdTRUE);
}

int el_sem_destroy(el_sem_t *sem)
{
    vSemaphoreDelete(*sem);
    return 0;
}

int el_mutex_create(el_mutex_t *mutex)
{
    *mutex = xSemaphoreCreateMutex();
    if (*mutex)
        return 0;
    return -1;
}

int el_mutex_lock(el_mutex_t *mutex)
{
    xSemaphoreTake(*mutex, portMAX_DELAY);
    return 0;
}

int el_mutex_trylock(el_mutex_t *mutex)
{
    return !(xSemaphoreTake(*mutex, 0) == pdTRUE);
}

int el_mutex_unlock(el_mutex_t *mutex)
{
    xSemaphoreGive(*mutex);
    return 0;
}

int el_mutex_destroy(el_mutex_t *mutex)
{
    vSemaphoreDelete(*mutex);
    return 0;
}

int el_spin_create(el_spinlock_t *spin)
{
    return el_mutex_create(spin);
}

int el_spin_lock(el_spinlock_t *spin)
{
    return el_mutex_lock(spin);
}

int el_spin_trylock(el_spinlock_t *spin)
{
    return el_mutex_trylock(spin);
}

int el_spin_unlock(el_spinlock_t *spin)
{
    return el_mutex_unlock(spin);
}

int el_spin_destroy(el_spinlock_t *spin)
{
    return el_mutex_destroy(spin);
}

long long el_ticks_get(void)
{
    return pdTICKS_TO_MS(xTaskGetTickCount());
}

void el_sleep_ms(int ms)
{
    vTaskDelay(pdMS_TO_TICKS(ms));
}

int el_thread_create(el_thread_t *thread, void *attr, int prio, 
                     void *(* fun)(void *), void *param)
{
    int rev;
    int STACK_SIZE = 20 * 1024;
    int prio2 = portPRIVILEGE_BIT | 2;
    rev = xTaskCreate((void *)fun, "NAME", STACK_SIZE, param, prio2, thread);
    return rev != pdPASS;
}
