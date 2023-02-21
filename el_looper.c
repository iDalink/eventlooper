#include "el_looper.h"

static void eve_quit_fun(el_event_t *event)
{

}

static void eve_nop_fun(el_event_t *event)
{
    
}

void el_looper_init(el_looper_t *looper)
{
    looper->event_list = NULL;
    el_sem_create(&looper->sem);
    el_mutex_create(&looper->mutex);
}

void el_looper_post_event(el_looper_t *looper, el_event_t *event)
{
    el_mutex_lock(&looper->mutex);
    if (looper->event_list)
    {
        el_event_add(looper->event_list, event);
    }
    else
    {
        looper->event_list = event;
    }
    el_mutex_unlock(&looper->mutex);
    el_sem_post(&looper->sem);
}

int el_looper_remove_event(el_looper_t *looper, el_event_t *event)
{
    int rev;
    el_mutex_lock(&looper->mutex);
    rev = el_event_remove(&looper->event_list, event);
    el_mutex_unlock(&looper->mutex);
    return rev;
}

void el_looper_run(el_looper_t *looper, int continous)
{
    el_event_t *event;
retry:
    el_mutex_lock(&looper->mutex);
    event = el_event_remove_first(&looper->event_list);
    el_mutex_unlock(&looper->mutex);
    if (!event)
    {
        if (continous)
        {
            el_sem_wait(&looper->sem);
            goto retry;
        }
        else
        {
            return;
        }
    }
    if (event->fire_cb == eve_quit_fun)
    {
        el_event_destroy(event);
        return;
    }
    el_event_fire(event);
    el_event_destroy(event);
    goto retry;
}

void el_looper_deinit(el_looper_t *looper)
{
    el_sem_destroy(&looper->sem);
    el_mutex_destroy(&looper->mutex);
}


const el_event_t *el_event_create_quit(void)
{
    el_event_t *event = el_event_create(eve_quit_fun);
    return event;
}

const el_event_t *el_event_create_nop(void)
{
    el_event_t *event = el_event_create(eve_nop_fun);
    return event;
}

