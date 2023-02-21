#include "el_looper.h"
#include <stdio.h>
#include "el_timer.h"

static void event_cb(el_event_t *event)
{
    printf("event fired:%p\n", event);
}

static void *new_thread(void *param)
{
    el_looper_t *looper = param;
    int count = 0;
    while (1)
    {
        if (count ++ == 5)
        {
            const el_event_t *event = el_event_create_quit();
            printf("post quit event:%p\n", event);
            el_looper_post_event(looper, (el_event_t *)event);
            break;
        }
        el_event_t *event = el_event_create(event_cb);
        printf("post event:%p\n", event);
        el_looper_post_event(looper, event);
        el_sleep_ms(1000);
    }
    return NULL;
}

static void timer_cb(el_timer_t *timer)
{
    printf("timer fired:%p\n", timer);
    //el_timer_destroy(timer);
    el_timer_start(timer);
}

static void *new_timer(void *param)
{
    el_looper_t *looper = param;
    int count = 0;
    el_timer_set_runloop(looper);
    while (1)
    {
        if (count++ == 1)
        {
            break;
        }
        el_timer_t *timer = el_timer_create(1000, timer_cb);
        el_timer_start(timer);
        printf("timer start:%p\n", timer);
        //el_sleep_ms(1000);
    }
    return NULL;
}

int main(void)
{
    el_thread_t thread;
    el_looper_t looper;
    el_looper_init(&looper);

    el_thread_create(&thread, NULL, 0, new_thread, &looper);
    el_thread_create(&thread, NULL, 0, new_timer, &looper);

    el_looper_run(&looper, true);

    el_looper_deinit(&looper);

    return 0;
}
