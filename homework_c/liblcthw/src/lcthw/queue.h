#ifndef lcthw_Queue_h
#define lcthw_Queue_h

#include<lcthw/list.h>

typedef List Queue;

#define Queue_create List_create
#define Queue_destroy List_destroy
#define Queue_send List_push
#define Queue_recv List_shift
#define Queue_peek List_first
#define Queue_count List_count

#define QUEUE_FOREACH(Q,V) LIST_FOREACH(Q,first,next,V)

#endif

