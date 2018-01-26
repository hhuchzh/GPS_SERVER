#include <errno.h>
#include <string.h>
#include "dispatcher.h"
#include "gps_user.h"
#include "logger.h"

SDispatcher *create_dispatcher(void)
{
	int i;
	SDispatcher *dispatcher = (SDispatcher *)calloc(sizeof(SDispatcher), 1);
	if (!dispatcher) {
		LOG_ERROR("create dispatcher failure");
		return NULL;
	}

	for (i = 0; i < ENGINE_NUM; i++) {
		dispatcher->array_engines[i] = create_engine(i);	
	}
	
	dispatcher->count = 0;
	LOG_INFO("create");
	return dispatcher;
}

void run_dispatcher(SDispatcher *dispatcher)
{
	int i;
	LOG_INFO("run");
	for (i = 0; i < ENGINE_NUM; i++) {
		run_engine(dispatcher->array_engines[i]);
	}
	dispatcher->count = 0;
}

void do_dispatch(SDispatcher *dispatcher, evutil_socket_t fd)
{ 
	if (dispatcher->count % ENGINE_NUM == 0) {
		dispatcher->count = 0;
	}
	
	LOG_INFO("egine %d, fd 0x%x", dispatcher->count, fd);
	create_gps_user(dispatcher->array_engines[dispatcher->count++], fd);
	return;
}


void stop_dispather(SDispatcher *dispatcher)
{
	int i;
	LOG_INFO("stop");
	for (i = 0; i < ENGINE_NUM; i++) {
		stop_engine(dispatcher->array_engines[i]);
	}
	dispatcher->count = 0;
	return;
}


void destroy_dispathcher(SDispatcher *dispatcher)
{
	int i;
	LOG_INFO("destroy");
	for (i = 0; i < ENGINE_NUM; i++) {
		destroy_engine(dispatcher->array_engines[i]);
	}
	free(dispatcher);
	
	return;
}

