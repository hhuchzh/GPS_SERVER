#include "listener.h"
#include "logger.h"

static void listener_cb(struct evconnlistener *conn, evutil_socket_t sock, 
	struct sockaddr *addr, int socklen, void *user)
{
	SListener *listener = (SListener *)user;
	LOG_DEBUG("receive a connection 0x%x", sock);
	do_dispatch(listener->dispatcher, sock);
}


SListener *create_listener(unsigned int port)
{

	SListener *listener = (SListener *)calloc(sizeof(SListener), 1);	
	if(!listener) {
		LOG_ERROR("create listener failure");
		return NULL;
	}
	memset(&listener->sin, 0, sizeof(struct sockaddr_in));
	listener->sin.sin_family = AF_INET;
	listener->sin.sin_port = htons(port);
	listener->base = event_base_new();
	if (!listener->base) {
		free(listener);
		return NULL;
	}

	listener->conn = evconnlistener_new_bind(listener->base, listener_cb, (void *)listener,
		LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, -1,
		(struct sockaddr *)&listener->sin, (int)sizeof(listener->sin));

	if (!listener->conn) {
		event_base_free(listener->base);
		free(listener);
		return NULL;
	}

	listener->dispatcher = create_dispatcher();
	if (!listener->dispatcher) {
		evconnlistener_free(listener->conn);
		event_base_free(listener->base);
		free(listener);	
	}
	return listener;
}


void run_listener(SListener * listener)
{
	LOG_INFO("run listener");
	if (!listener) {
		LOG_ERROR("run listener failure, null pointer");
		return;
	}
	run_dispatcher(listener->dispatcher);
	event_base_dispatch(listener->base);
	
}


void stop_listener(SListener * listener)
{
	LOG_INFO("stop");
	event_base_loopexit(listener->base, NULL);
	stop_dispather(listener->dispatcher);
}


void destroy_listener(SListener *listener)
{
	LOG_INFO("destroy");
	event_base_free(listener->base);
	evconnlistener_free(listener->conn);
	destroy_dispathcher(listener->dispatcher);
	
}

