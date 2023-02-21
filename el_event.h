#ifndef __EL_EVENT_H__
#define __EL_EVENT_H__

#include "el_port.h"

typedef struct el_event_t el_event_t;
typedef void (* el_free_cb_t)(void *ptr);
typedef void (* el_fire_cb_t)(el_event_t *event);


typedef struct
{
    void *user_data1;
    void *user_data2;
    int   user_data3;
} el_event_payload_t;


typedef struct el_event_t
{
    el_free_cb_t free_cb;
    el_fire_cb_t fire_cb;
    void *next;

    el_event_payload_t payload;
} el_event_t;

el_event_t * el_event_create(el_fire_cb_t fire);
int el_event_count(el_event_t *event);
el_event_t *el_event_next(el_event_t *list);

void el_event_add(el_event_t *list, el_event_t *event);
int el_event_remove(el_event_t **list, el_event_t *event);
el_event_t *el_event_remove_first(el_event_t **list);
void el_event_fire(el_event_t *event);
void el_event_destroy(el_event_t *event);

#endif
