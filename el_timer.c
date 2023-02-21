#include "el_timer.h"

typedef struct el_timer_mgr
{
    el_timer_t *timer;
    int inited;
    el_looper_t *looper;
    el_thread_t thread;
    el_mutex_t mutex;
} el_timer_mgr;

static el_timer_mgr mgr = {0};

static void add_timer(el_timer_t *list, el_timer_t *timer);
static int remove_timer(el_timer_t **list, el_timer_t *timer);
static el_timer_t *found_timeout_one(el_timer_t *list);

static void timer_event_cb_t(el_event_t *event)
{
    el_timer_t *timer = event->payload.user_data1;
    //el_timer_mgr *mgr = event->payload.user_data2;
    timer->event = NULL;
    timer->state = EL_TIMER_STATE_FIRED;
    timer->fire(timer);
}

static void *timer_thread(void *param)
{
    el_timer_mgr *mgr = param;
    while (1)
    {
        el_timer_t *timer;
        el_mutex_lock(&mgr->mutex);
retry:
        timer = found_timeout_one(mgr->timer);
        if (timer)
        {
            remove_timer(&mgr->timer, timer);
            el_event_t *event = el_event_create(timer_event_cb_t);
            event->payload.user_data1 = timer;
            event->payload.user_data2 = mgr;
            timer->event = event;
            el_looper_post_event(mgr->looper, event);
            goto retry;
        }
        el_mutex_unlock(&mgr->mutex);
        el_sleep_ms(2);
    }
    return NULL;
}

void el_timer_set_runloop(el_looper_t *looper)
{
    mgr.looper = looper;
}

el_timer_t *el_timer_create(int duration, el_timer_fire_t fire)
{
    el_timer_t *timer = el_mem_malloc(sizeof(*timer));
    timer->state = EL_TIMER_STATE_IDLE;
    timer->duration = duration;
    timer->fire = fire;
    timer->next = NULL;
    timer->event = NULL;
    timer->user_data = NULL;
    return timer;
}

void el_timer_start(el_timer_t *timer)
{
    int state = timer->state;
    if (state == EL_TIMER_STATE_TIMING)
    {
        printf("el_timer_start:%p for dur:%d state:%d err\n", 
               timer, timer->duration, state);
        return;
    }
    timer->state = EL_TIMER_STATE_TIMING;
    timer->begin_time = el_ticks_get();
    timer->next = NULL;

    if (!mgr.inited)
    {
        if (!mgr.looper)
        {
            printf("You might forget set timer`s looper\n");
            return;
        }
        mgr.inited = 1;
        el_mutex_create(&mgr.mutex);
        el_thread_create(&mgr.thread, NULL, 0, timer_thread, &mgr);
    }

    el_mutex_lock(&mgr.mutex);
    if (!mgr.timer)
    {
        mgr.timer = timer;
    }
    else
    {
        add_timer(mgr.timer, timer);
    }
    el_mutex_unlock(&mgr.mutex);
}

void el_timer_stop(el_timer_t *timer)
{
    int state = timer->state;
    if (state != EL_TIMER_STATE_TIMING)
    {
        return;
    }
    timer->state = EL_TIMER_STATE_IDLE;
    el_mutex_lock(&mgr.mutex);
    remove_timer(&mgr.timer, timer);
    if (timer->event)
    {
        el_looper_remove_event(mgr.looper, timer->event);
        el_event_destroy(timer->event);
        timer->event = NULL;
    }
    el_mutex_unlock(&mgr.mutex);
}

void el_timer_destroy(el_timer_t *timer)
{
    el_timer_stop(timer);
    el_mem_free(timer);
}







static el_timer_t *found_timeout_one(el_timer_t *list)
{
    long long ticks = el_ticks_get();
    el_timer_t *timer = list;
    while (timer)
    {
        if (timer->begin_time + timer->duration <= ticks)
        {
            return timer;
        }
        if (timer == timer->next)
        {
            printf("Timer list internal failure for:%p!\n", timer);
            while(1);
        }
        timer = timer->next;
    }
    return NULL;
}

static void add_timer(el_timer_t *list, el_timer_t *timer)
{
    el_timer_t *add = timer;
    timer = list;
    while (timer->next)
    {
        timer = timer->next;
    }
    timer->next = add;
}

static int remove_timer(el_timer_t **list, el_timer_t *timer)
{
    el_timer_t *tim_prev = NULL;
    el_timer_t *tim      = *list;

    while (tim)
    {
        if (tim == timer)
        {
            break;
        }
        tim_prev = tim;
        tim = tim->next;
    }

    if (!tim) return -1;
    if (tim_prev)
        tim_prev->next = tim->next;
    else
        *list = tim->next;

    tim->next = NULL;
    return 0;
}
