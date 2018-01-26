#ifndef __MSG_H__
#define __MSG_H__

#include <stdio.h>
#include "crc_itu.h"

#define PROTOCOL_NUM_INIT 0x01
#define PROTOCOL_NUM_DATA 0x12
#define PROTOCOL_NUM_HEATBEAT 0x13
#define PROTOCOL_NUM_INVALID 0xff


typedef struct _MsgHandshakeReq {
	unsigned short start_pos;
	unsigned char len;
	unsigned char protocol_num;
	unsigned char device_id[8];
	unsigned short seq;
	unsigned short crc;
	unsigned short stop_pos;
}SMsgHandshakeReq;

typedef struct _MsgInitRes {
	unsigned short start_pos;
	unsigned char len;
	unsigned char protocol_num;
	unsigned short seq;
	unsigned short crc;
	unsigned short stop_pos;
}SMsgInitRes;


typedef struct _MsgDataReq {
	unsigned short start_pos;
	unsigned char len;
	unsigned char protocol_num;
	unsigned char year;
	unsigned char month;
	unsigned char day;
	unsigned char hour;
	unsigned char minute;
	unsigned char second;
	unsigned char gps_info_len;
	unsigned char gps_pos_num;
	unsigned int latitude;
	unsigned int longitude;
	unsigned char speed;
	unsigned char rp_dp_flag;			/*0:real position, 1  Differential positon*/
	unsigned char positioned_flag; 		/*1: positioned, 0 not positioned*/
	unsigned char latitude_type;	/*0: east, 1 west*/
	unsigned char longitude_type;	/*0: north, 1 south*/
	unsigned short heading;
	unsigned short mcc;
	unsigned char mnc;
	unsigned short lac;
	unsigned int cell_id;
	unsigned short seq;
	unsigned short crc;
	unsigned short stop_pos;
	
}SMsgDataReq;

typedef struct _MsgHeartbeatReq {
	unsigned short start_pos;
	unsigned char len;
	unsigned char protocol_num;
	/*terminal info*/
	unsigned char oil_power_flag;		/*0: disconnect, 1: connect*/
	unsigned char positioned_flag;		/*0: positioned, 1:not positioned*/
	unsigned char alarm_level;			/*4: SOS, 3: low power, 2: no power, 1: sharking, 0: normal*/
	unsigned char power_flag;			/*1: connect, 0: disconnect*/
	unsigned char acc_flag; 			/*1: high, 0:low*/
	unsigned char arm_flag;				/*1: arm, 0: disarm*/
	unsigned char voltage_level;
	unsigned char single_level;
	unsigned short alarm_language;
	unsigned short seq;
	unsigned short crc;
	unsigned short stop_pos;
}SMsgHeartbeatReq;


typedef struct _MsgHeartbeatRes {
	unsigned short start_pos;
	unsigned char len;
	unsigned char protocol_num;
	unsigned short seq;
	unsigned short crc;
	unsigned short stop_pos;
}SMsgHeartbeatRes;

int valid_msg_header(const unsigned char *msg, int size);

int get_protocl_nu(const unsigned char *msg, int size);

int parse_msg_handshake_req(const unsigned char *msg, int size, SMsgHandshakeReq *req);
int generate_msg_init_resp(unsigned char *msg, int size, unsigned short seq);

int parse_msg_data_req(const unsigned char *msg, int size, SMsgDataReq *req);

int parse_msg_heartbeat_req(const unsigned char *msg, int size, SMsgHeartbeatReq *req);
int generate_msg_heartbeat_resp(unsigned char *msg, int size, unsigned short seq);


#endif
