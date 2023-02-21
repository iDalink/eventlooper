#ifndef __EL_PORT_ESP32__
#define __EL_PORT_ESP32__
#include "freertos/FreeRTOS.h"
#include <freertos/semphr.h>
#include <freertos/task.h>

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

typedef SemaphoreHandle_t el_sem_t;

typedef SemaphoreHandle_t el_mutex_t;

typedef el_mutex_t el_spinlock_t;

typedef TaskHandle_t el_thread_t;


#endif