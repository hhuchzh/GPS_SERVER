#ifndef __LISTENER_H__
#define __LISTENER_H__

#include <stdio.h>
#include <string.h>
#include <event2/bufferevent.h>  
#include <event2/buffer.h>  
#include <event2/listener.h>  
#include <event2/util.h>  
#include <event2/event.h>
#include "dispatcher.h"

typedef struct _Listener {
	struct event_base *base;
	struct evconnlistener *conn;
	struct sockaddr_in sin;
	SDispatcher *dispatcher;
}SListener;


SListener * create_listener(unsigned int port);
void run_listener(SListener * listener);
void stop_listener(SListener * listener);
void destroy_listener(SListener *listener);

#endif
