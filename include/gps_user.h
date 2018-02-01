#ifndef __GPS_USER_H__
#define __GPS_USER_H__

#include <event2/bufferevent.h>  
#include <event2/buffer.h>  
#include <event2/util.h>  
#include <event2/event.h>
#include <stdio.h>
#include "engine.h"
#include "msg.h"



#define MAX_CHECK_NUM 3

enum UserStatus {
	USER_CONNECT = 0x0,
	USER_VALID = 0x1,
};

typedef struct _GpsUser {
	SEngine *engine;
	enum UserStatus status;
	evutil_socket_t fd;
	struct event *event_timer;	
	struct bufferevent *bev_socket; 
	int update;/*1: receive gps client msg, 0 not*/
	int check_no;/*max 3*/
	unsigned short seq;
	unsigned char device_id[8];
}SGpsUser;


SGpsUser *create_gps_user(SEngine *engine, evutil_socket_t fd);
void destroy_gps_user(SGpsUser * user);

#endif
