#ifndef __EL_LOOPER_H__
#define __EL_LOOPER_H__

#include "el_event.h"

typedef struct 
{
    el_event_t *event_list;
    el_sem_t sem;
    el_mutex_t mutex;
} el_looper_t;

void el_looper_init(el_looper_t *looper);

void el_looper_post_event(el_looper_t *looper, el_event_t *event);
int  el_looper_remove_event(el_looper_t *looper, el_event_t *event);

void el_looper_run(el_looper_t *looper, int continous);

void el_looper_deinit(el_looper_t *looper);

const el_event_t *el_event_create_quit(void);
const el_event_t *el_event_create_nop(void);

#endif
