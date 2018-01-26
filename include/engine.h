#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <event2/bufferevent.h>  
#include <event2/buffer.h>  
#include <event2/util.h>  
#include <event2/event.h>
#include <pthread.h> 
#include <stdio.h>


enum EngineStatus {
	ENGINE_STATUS_INIT = 0x00,
	ENGINE_STATUS_RUN = 0x01,
	ENGINE_STATUS_STOP = 0x02,
	ENGINE_STATUS_STOPPED = 0x02,
};

typedef struct _Engine {
	int engine_no;
	struct event_base *base;
	pthread_t tid;
	enum EngineStatus status;
}SEngine;

SEngine *create_engine(int no);
void run_engine(SEngine *engine);
void stop_engine(SEngine *engine);
int destroy_engine(SEngine *engine);

#endif
