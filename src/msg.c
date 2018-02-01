#include "msg.h"
#include <assert.h>
#include <string.h>
#include "logger.h"

#define DUMP_MSG 1

int valid_msg_header(const unsigned char *msg, int size)
{
	if (size < 2) {
		return 0;
	}
	
	if( ((unsigned short)(msg[0] << 8 | msg[1])) != ((unsigned short)0x7878))
	{
		return 0;
	}

	return 1;
}


int get_protocl_nu(const unsigned char *msg, int size)
{
	if (size < 4) {
		return PROTOCOL_NUM_INVALID;
	}
	return msg[3];
}

int parse_msg_handshake_req(const unsigned char *msg, int size, SMsgHandshakeReq *req)
{
	unsigned int len = 0;
	int i = 0;
	int j = 0;
	i = i;
	j = j;

	//assert(msg);
	//assert(req);
	//assert(size >= 18);

	if (!msg || !req || size < 18) {
		LOG_ERROR("invalid handshake req");
		return 0;
	}
	
	req->start_pos = (unsigned short)(msg[0] << 8 | msg[1]);
	req->len = msg[2];
	len = req->len + 5;
	
	if (req->start_pos != (unsigned short)0x7878) {
		LOG_WARN("invalid start position");
		return 0;
	}

	if (len != 18) {
		LOG_WARN("invalid len: %d", len);
		return 0;
	}

	req->protocol_num = msg[3];
	memcpy(req->device_id, &msg[4], 8);
	req->seq = (unsigned short)(msg[12] << 8 | msg[13]);
	req->crc = (unsigned short)(msg[14] << 8 | msg[15]);
	if (is_crc16_good(msg + 2, 12, req->crc) == 0) {
		LOG_WARN("invalid crc");
		return 0;
	}

	req->stop_pos = (unsigned short)(msg[16] << 8 | msg[17]);
	if (req->stop_pos != 0x0D0A) {
		LOG_WARN("invalid end position");
	}

	LOG_DEBUG("parse successfully\n");
#if DUMP_MSG	
	for (i = 0; i < len / 8; i++) {	
		for (j = 0; j < 8; j++) {
			printf("0x%02X ", msg[8 * i + j]);
		}
		printf("\n");
	}

	for (j = 0; j < len % 8; j ++) {
		printf("0x%02X ", msg[8 * i + j]);
	}
	printf("\n");
#endif	

	return 1;	
}



int generate_msg_init_resp(unsigned char *msg, int size, unsigned short seq)
{
	int i = 0;
	int j = 0;
	int len = 10;
	unsigned short crc = 0;
	i = i;
	j= j;
	assert(msg);
	assert(size >= 10);

	if (!msg || size < 10) {
		LOG_ERROR("invalid init request");
		return 0;
	}

	LOG_DEBUG("seq 0x%02X\n", seq);
	msg[0] = 0x78;
	msg[1] = 0x78;
	msg[2] = 0x05;
	msg[3] = 0x01;
	msg[4] = (unsigned char) (seq >> 8 & 0x00ff);
	msg[5] = (unsigned char) (seq & 0x00ff);
	crc = get_crc_16(msg + 2, 4);
	msg[6] = (unsigned char)(crc >> 8 & 0x00ff);
	msg[7] = (unsigned char)(crc & 0xff);
	msg[8] = 0x0D;
	msg[9] = 0x0A;

#if DUMP_MSG
	for (i = 0; i < len / 8; i++) {
		for (j = 0; j < 8; j++) {
			printf("0x%02X ", msg[i * 8 + j]);
		}
		printf("\n");
	}

	for (j = 0; j < len % 8; j++) {
		printf("0x%02X ", msg[i * 8 + j]);
	}
	printf("\n");
#endif

	return len;	

}

int parse_msg_data_req(const unsigned char *msg, int size, SMsgDataReq *req)
{
	unsigned int len = 0;
	int i = 0;
	int j = 0;
	i = i;
	j = j;

	//assert(msg);
	//assert(req);
	//assert(size >= 36);

	if (!msg || !req || size < 36) {
		LOG_ERROR("invalid data reqest");
		return 0;
	}
	
	req->start_pos = (unsigned short)(msg[0] << 8 | msg[1]);
	req->len = msg[2];
	len = req->len + 5;
	
	if (req->start_pos != (unsigned short)0x7878) {
		LOG_WARN("invalid start position");
		return 0;
	}

	if (len != 36) {
		LOG_WARN("invalid len: %d\n", len);
		return 0;
	}

	req->protocol_num = msg[3];
	req->year = msg[4];
	req->month = msg[5];
	req->day = msg[6];
	req->hour = msg[7];
	req->minute = msg[8];
	req->second = msg[9];
	req->gps_info_len = (unsigned char)(msg[10] >> 4 & 0x0f);
	req->gps_pos_num = (unsigned char)(msg[10] & 0x0f);
	req->latitude = (unsigned int)(msg[11] << 24 | msg[12] << 16 | msg[13] << 8 | msg[14]);
	req->longitude = (unsigned int)(msg[15] << 24 | msg[16] << 16 | msg[17] << 8 | msg[18]);
	req->speed = msg[19];
	req->rp_dp_flag = (unsigned char)(msg[20] >> 5 & 0x01);
	req->positioned_flag = (unsigned char)(msg[20] >> 4 & 0x01);
	req->latitude_type = (unsigned char)(msg[20] >> 3 & 0x01);
	req->longitude_type = (unsigned char)(msg[20] >> 2 & 0x01);
	req->heading = (unsigned short)((msg[20] & 0x03) << 8 | msg[21]);
	req->mcc = (unsigned short)(msg[22] << 8 | msg[23]);
	req->mnc = msg[24];
	req->lac = (unsigned short)(msg[25] << 8 | msg[26]);
	req->cell_id = (unsigned int)((msg[27] <<16 | msg[28] << 8 | msg[29]) & 0x00ffffff);
	req->seq = (unsigned short)(msg[30] << 8 | msg[31]);
	req->crc = (unsigned short)(msg[32] << 8 | msg[33]);
	if (is_crc16_good(msg + 2, 30, req->crc) == 0) {
		LOG_WARN("invalid crc");
		return 0;
	}

	req->stop_pos = (unsigned short)(msg[34] << 8 | msg[35]);
	if (req->stop_pos != 0x0D0A) {
		LOG_WARN("invalid end position\n");
	}

	LOG_DEBUG("parse successfully");
#if DUMP_MSG	
	for (i = 0; i < len / 8; i++) { 
		for (j = 0; j < 8; j++) {
			printf("0x%02X ", msg[8 * i + j]);
		}
		printf("\n");
	}

	for (j = 0; j < len % 8; j ++) {
		printf("0x%02X ", msg[8 * i + j]);
	}
	printf("\n");
#endif	

	return 1;	


}

int parse_msg_heartbeat_req(const unsigned char *msg, int size, SMsgHeartbeatReq *req)
{
	unsigned int len = 0;
	//assert(msg);
	//assert(size >= 15);
	//assert(req);

	if (!msg || !req || size < 15) {
		LOG_ERROR("invalid heartbeat req");
		return 0;
	}

	req->start_pos = (unsigned short)(msg[0] << 8 | msg[1]);
	req->len = msg[2];	
	req->protocol_num = msg[3];
	len = req->len + 5;
	if (req->start_pos != (unsigned short)0x7878) {
		LOG_WARN("invalid start position");
		return 0;
	}
	
	if (len != 15) {
		LOG_WARN("invalid len: %d", len);
		return 0;
	}
	
	req->protocol_num = msg[3];
	req->oil_power_flag = (unsigned char)(msg[4] >> 7 & 0x01);
	req->positioned_flag = (unsigned char)(msg[4] >> 6 & 0x01);
	req->alarm_level = (unsigned char)(msg[4] >> 3 & 0x07);
	req->power_flag = (unsigned char)(msg[4] >> 2 & 0x01);
	req->acc_flag = (unsigned char)(msg[4] >> 1 & 0x01);
	req->arm_flag = (unsigned char)(msg[4] & 0x01);
	req->voltage_level = msg[5];
	req->alarm_language =(unsigned short)(msg[6] << 8 | msg[7]);
	req->single_level = msg[8];
	req->seq = (unsigned short)(msg[9] << 8 | msg[10]);
	req->crc = (unsigned short)(msg[11] << 8 | msg[12]);

	if (is_crc16_good(msg + 2, 9, req->crc) == 0) {
		LOG_WARN("invalid crc");
		return 0;
	}
	
	req->stop_pos = (unsigned short)(msg[13] << 8 | msg[14]);

	if (req->stop_pos != 0x0D0A) {
		LOG_WARN("invalid end position");
	}

	return 1;
}

int generate_msg_heartbeat_resp(unsigned char *msg, int size, unsigned short seq)
{
	int i = 0;
	int j = 0;
	int len = 10;
	unsigned short crc = 0;

	i = i;
	j = j;
	assert(msg);
	assert(size >= 10);

	if (!msg || size < 10) {
		LOG_ERROR("invalid heartbeat resp");
	}

	LOG_DEBUG("seq 0x%02X\n", seq);

	msg[0] = 0x78;
	msg[1] = 0x78;
	msg[2] = 0x05;
	msg[3] = 0x13;
	msg[4] = (unsigned char) (seq >> 8 & 0x00ff);
	msg[5] = (unsigned char) (seq & 0x00ff);
	crc = get_crc_16(msg + 2, 4);
	msg[6] = (unsigned char)(crc >> 8 & 0x00ff);
	msg[7] = (unsigned char)(crc & 0xff);	
	msg[8] = 0x0D;
	msg[9] = 0x0A;
#if DUMP_MSG
		for (i = 0; i < len / 8; i++) {
			for (j = 0; j < 8; j++) {
				printf("0x%02X ", msg[i * 8 + j]);
			}
			printf("\n");
		}
	
		for (j = 0; j < len % 8; j++) {
			printf("0x%02X ", msg[i * 8 + j]);
		}
		printf("\n");
#endif

	return 10;
}

