#ifndef __EL_TIMER_H__
#define __EL_TIMER_H__

#include "el_looper.h"

#define EL_TIMER_STATE_IDLE   0
#define EL_TIMER_STATE_TIMING 1
#define EL_TIMER_STATE_FIRED  2

typedef struct el_timer_t el_timer_t;

typedef void (*el_timer_fire_t)(el_timer_t *timer);

typedef struct el_timer_t
{
    int state;
    int duration;
    el_timer_fire_t fire;
    el_event_t *event;
    long long begin_time;
    void *user_data;
    void *next;
} el_timer_t;

void el_timer_set_runloop(el_looper_t *looper);

el_timer_t *el_timer_create(int duration, el_timer_fire_t fire);
void el_timer_start(el_timer_t *timer);
void el_timer_stop(el_timer_t *timer);

void el_timer_destroy(el_timer_t *timer);

#endif