#ifndef __DISPACHER_H__
#define __DISPACHER_H__

#include <event2/bufferevent.h>  
#include <event2/buffer.h>  
#include <event2/util.h>  
#include <event2/event.h>
#include <stdlib.h>
#include "engine.h"

#define ENGINE_NUM (4)

typedef struct _Dispatcher {
	SEngine *array_engines[ENGINE_NUM];
	unsigned int count;
}SDispatcher;


SDispatcher *create_dispatcher(void);
void run_dispatcher(SDispatcher *dispatcher);
void do_dispatch(SDispatcher *dispatcher, evutil_socket_t fd);
void stop_dispather(SDispatcher *dispatcher);
void destroy_dispathcher(SDispatcher *dispatcher);

#endif