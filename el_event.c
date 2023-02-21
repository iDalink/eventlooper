#include "el_event.h"

static void event_free(void *ptr)
{
    el_mem_free(ptr);
}

el_event_t *el_event_create(el_fire_cb_t fire)
{
    el_event_t *event = el_mem_malloc(sizeof(*event));
    event->next = NULL;
    event->free_cb = event_free;
    event->fire_cb = fire;
    event->payload.user_data1 = NULL;
    event->payload.user_data2 = 0;
    return event;
}

int el_event_count(el_event_t *list)
{
    int count = 0;
    el_event_t *event = list;
    while (event)
    {
        event = event->next;
        count++;
    }
    return count;
}

el_event_t *el_event_next(el_event_t *event)
{
    return event->next;
}

void el_event_add(el_event_t *list, el_event_t *event)
{
    el_event_t *add = event;
    event = list;
    while (event->next)
    {
        event = event->next;
    }
    event->next = add;
}

int el_event_remove(el_event_t **list, el_event_t *event)
{
    el_event_t *eve_prev = NULL;
    el_event_t *eve      = *list;

    while (eve)
    {
        if (eve == event)
        {
            break;
        }
        eve = event->next;
        eve_prev = eve;
    }

    if (!eve) return -1;
    if (eve_prev)
        eve_prev->next = eve->next;
    else
        *list = eve->next;

    event->next = NULL;
    return 0;
}

el_event_t *el_event_remove_first(el_event_t **list)
{
    el_event_t *event = *list;
    if (event)
    {
        *list = event->next;
        event->next = NULL;
    }
    return event;
}

void el_event_fire(el_event_t *event)
{
    event->fire_cb(event);
}

void el_event_destroy(el_event_t *event)
{
    event->free_cb(event);
}


