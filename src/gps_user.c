#include <assert.h>
#include <stdlib.h>
#include "gps_user.h"
#include <string.h>
#include "logger.h"
#include "occi.h"
#define BUFFER_SIZE 1024

using namespace std;
using namespace oracle::occi;

Environment *env;
Connection  *con;

static int connect_db()
{
    string name = "youtu";
    string pass = "Bagejiadao321";
    string srvName = "121.41.92.30:1521/orcl";
    env = Environment::createEnvironment(Environment::DEFAULT);

    con = env->createConnection(name, pass, srvName);
    if(con==NULL)
    {
        LOG_ERROR("create Connection failed");
        return -1;
		
    }
    LOG_DEBUG("success createConnection!");
    return 1;

}


static void disconnect_db()
{
    env->terminateConnection (con);	
    Environment::terminateEnvironment (env);
}
static int  check_db_Time()
{
  /*
 *    * simple test method to select data from
 *       * the employees table and display the results
 *       */

  	Statement *pStmt = NULL;	  // Statement¶ÔÏó
	pStmt = con->createStatement();
	if(NULL == pStmt){
		LOG_ERROR("createStatement error.\n");
		return -1;
	 }

	 //²éÑ¯Êý¾Ý¿âtime
	 string strTemp;
	 ResultSet *pRs = pStmt->executeQuery( "SELECT TO_CHAR(SYSDATE, 'YYYY-MM-DD HH24:MI:SS') FROM DUAL");

	 if(pRs==NULL)
	 	return -1;
	 while(pRs->next()) 
	{
		strTemp = pRs->getString(1);
		LOG_DEBUG("db time:%s.\n", strTemp.c_str());
	 	// intÀàÐÍÈ¡ÖµÓÃgetInt()
		break;
	}

 
	pStmt->closeResultSet(pRs);
	con->terminateStatement(pStmt);
	return 1;
	
}

static int Write_DB(SMsgDataReq *data,char device_id[8])
{
	Statement *pStmt = NULL;	  // Statement¶ÔÏó
	pStmt = con->createStatement();
	if(NULL == pStmt){
		LOG_ERROR("createStatement error.\n");
		return -1;
	}

	char time[50];
	//INSERT INTO FLOOR VALUES ( to_date ( '2007-12-20 18:31:34' , 'YYYY-MM-DD HH24:MI:SS' ) ) ;
	sprintf(time,"20%d-%d-%d %d-%d-%d",data->year,data->month,data->day,data->hour,data->minute,data->second);
	
	unsigned int id;

	char sql[1000]={0};
	string sql_sort;
	//sql_sort="INSERT INTO B_GPS_INFO (device_id, latitude,longitude,heading,speed,lat_type,lng_type,cell_id,gps_time)\ 
	//	                        VALUES('"&id&"','"&data->latitude&"','"&data->longitude&"','"&data->heading&"','"&data->speed&"',\
	//	                        '"&data->latitude_type&"','"&data->longitude_type&"','"&data->cell_id&"',to_data(time,'YYYY-MM-DD HH24:MI:SS'))";
	sprintf(sql, "insert into B_GPS_INFO(device_id, latitude,longitude,heading,speed,lat_type,lng_type,cell_id,gps_time) values(%llu, %d, %d, %d, %d, %d, %d,to_date(:1,'YYYY-MM-DD HH24:MI:SS')", id, data->latitude,data->latitude,data->latitude,data->latitude,data->latitude,data->latitude,data->latitude);
	
	pStmt->setString(1, time);
	//--------²åÈë---------
	// Ö¸¶¨DMLÎª×Ô¶¯commit
	pStmt->setAutoCommit(TRUE);
	// ÉèÖÃÖ´ÐÐµÄSQLÓï¾
	//pStmt->setSQL("INSERT INTO B_GPS_INFO (device_id, latitude,longitude,heading,speed,lat_type,lng_type,cell_id,gps_time) VALUES ('"++"', 432443,65432,2,50,3435,498,123456,to_date('2004/05/07 13:23:44','yyyy/mm/dd hh24:mi:ss'))");
	pStmt->setSQL(sql);
	// Ö´ÐÐSQLÓï¾ä
	unsigned int nRet = pStmt->executeUpdate();
	if(nRet == 0) {
		LOG_DEBUG("executeUpdate insert error.\n");
		return -1;
	}

	//pStmt->closeResultSet(nRet);
	con->terminateStatement(pStmt);
	return 1;

}


static int process_handshake_request(SGpsUser *user, unsigned char *msg, size_t sz)
{
	int ret = 1;
	int len = 0;
	SMsgHandshakeReq req;
	LOG_DEBUG("[Engine:%d][FD:0x%x]process handshake msg", user->engine->engine_no, user->fd);
	ret = parse_msg_handshake_req(msg, (int)sz, &req);
	if (ret == 1) {	
		if (((user->seq + 1) % 0xffff)  != (req.seq % 0xffff)) {
			LOG_WARN("[Engine:%d][FD:0x%x]seq no continous, pre:0x%x cur:0x%x", user->engine->engine_no, user->fd, user->seq, req.seq);
		}
		user->seq = req.seq;
		user->update = 1;
	 	memcpy(user->device_id,req.device_id,8);	
		LOG_DEBUG("[Engine:%d][FD:0x%x]process handshake msg, seq[%d]", user->engine->engine_no, user->fd, req.seq);
		unsigned char msg_resp[BUFFER_SIZE] = {0};
		len = generate_msg_init_resp(msg_resp,BUFFER_SIZE,req.seq);
		bufferevent_write(user->bev_socket, msg_resp, len);
		user->status = USER_VALID;
	}

	return ret;
}

static int process_data_request(SGpsUser *user, unsigned char *msg, size_t sz)
{
	int ret = 1;
	int len = 0;
	SMsgDataReq req;
	LOG_DEBUG("[Engine:%d][FD:0x%x]process data msg", user->engine->engine_no, user->fd);
	ret = parse_msg_data_req(msg, (int)sz, &req);
	if (ret == 1) {	
		if (((user->seq + 1) % 0xffff)  != (req.seq % 0xffff)) {
			LOG_WARN("[Engine:%d][FD:0x%x]seq no continous, pre:0x%x cur:0x%x", user->engine->engine_no, user->fd, user->seq, req.seq);
		}

		user->seq = req.seq;
		user->update = 1;
		LOG_DEBUG("[Engine:%d][FD:0x%x]process data msg, seq[%d]", user->engine->engine_no, user->fd, req.seq);
		/*Fix me*/
                connect_db();
                check_db_Time();
		//Write_DB(&req,user->device_id);
	}

	return ret;
}


static int process_heartbeat_request(SGpsUser *user, unsigned char *msg, size_t sz)
{
	int ret = 1;
	int len = 0;
	SMsgHeartbeatReq req;	
	LOG_DEBUG("[Engine:%d][FD:0x%x]process heartbeat msg", user->engine->engine_no, user->fd);
	ret = parse_msg_heartbeat_req(msg, (int)sz, &req);
	if (ret == 1) {	
		if (((user->seq + 1) % 0xffff)  != (req.seq % 0xffff)) {
			LOG_WARN("[Engine:%d][FD:0x%x]seq no continous, pre:0x%x cur:0x%x", user->engine->engine_no, user->fd, user->seq, req.seq);
		}
		user->seq = req.seq;		
		user->update = 1;
		LOG_DEBUG("[Engine:%d][FD:0x%x]process heartbeat msg, seq[%d]", user->engine->engine_no, user->fd, req.seq);
		unsigned char msg_resp[BUFFER_SIZE] = {0};
		len = generate_msg_heartbeat_resp(msg_resp,BUFFER_SIZE, req.seq);
		bufferevent_write(user->bev_socket, msg_resp, len);		
	}

	return ret;

}

static void gps_user_write_cb(struct bufferevent *bev, void *user_data)  
{
	SGpsUser *user = (SGpsUser *)user_data;
	LOG_DEBUG("[Engine:%d][FD:0x%x]write callback", user->engine->engine_no, user->fd);

	return;
}  


static void gps_user_read_cb(struct bufferevent *bev, void *user_data)  
{  
    struct evbuffer *input =bufferevent_get_input(bev);
	SGpsUser *user = (SGpsUser *)user_data;
    size_t sz = evbuffer_get_length(input); 
	int msg_type = PROTOCOL_NUM_INVALID;
	LOG_DEBUG("[Engine:%d][FD:0x%x]read callback", user->engine->engine_no, user->fd);
    if (sz > 0)  {
        unsigned char msg[BUFFER_SIZE] = {'\0'};  
        bufferevent_read(bev, msg, sz);
		
		// init message
		//unsigned char tmp[18] = {0x78, 0x78, 0x0D, 0x01, 0x01, 0x23, 0x45, 0x67, 0x89, 0x01, 0x23, 0x45, 0x00, 0x01, 0x8C, 0xDD, 0x0D, 0x0A};
		//sz = 18;
		//memcpy(msg, tmp, 18);

		 //data message
		//unsigned char tmp[36] = {0x78, 0x78, 0x1F, 0x12, 0x0B, 0x08, 0x1D, 0x11, 0x2E, 0x10, 0xCF, 0x02, 0x7A, 0xC7, 0xEB, 0x0C, 0x46, 0x58, 0x49, 0x00, 0x14, 0x8F, 0x01, 0xCC, 0x00, 0x28, 0x7D, 0x00, 0x1F, 0xB8, 0x00, 0x03, 0x80, 0x81, 0x0D, 0x0A};
		//sz = 36;
		//memcpy(msg, tmp, 36);

		// heartbeat message
		//unsigned char tmp[36] = {0x78, 0x78, 0x1F, 0x12, 0x0B, 0x08, 0x1D, 0x11, 0x2E, 0x10, 0xCF, 0x02, 0x7A, 0xC7, 0xEB, 0x0C, 0x46, 0x58, 0x49, 0x00, 0x14, 0x8F, 0x01, 0xCC, 0x00, 0x28, 0x7D, 0x00, 0x1F, 0xB8, 0x00, 0x03, 0x80, 0x81, 0x0D, 0x0A};
		//sz = 36;
		//memcpy(msg, tmp, 36);

		if (valid_msg_header(msg, sz) == 0) {
			LOG_ERROR("[Engine:%d][FD:0x%x]invalid message header", user->engine->engine_no, user->fd);
			return;
		}	
		msg_type = get_protocl_nu(msg, sz);
		if (PROTOCOL_NUM_INIT == msg_type) {
			if (0 == process_handshake_request(user, msg, sz)) {
				LOG_ERROR("[Engine:%d][FD:0x%x]invalid heartbeat request", user->engine->engine_no, user->fd);
				destroy_gps_user(user);
			}
		} else if (PROTOCOL_NUM_DATA == msg_type) {
			if (user->status == USER_VALID) {
				process_data_request(user, msg, sz);
			} else {
				LOG_ERROR("[Engine:%d][FD:0x%x]invalid data request", user->engine->engine_no, user->fd);			
				destroy_gps_user(user);
			}
		} else if (PROTOCOL_NUM_HEATBEAT == msg_type) {
			process_heartbeat_request(user, msg, sz);
		} else {
			LOG_ERROR("[Engine:%d][FD:0x%x]invalid protocol number %d", user->engine->engine_no, user->fd, msg_type);			
			if (user->status != USER_VALID) {
				destroy_gps_user(user);
			}
		}
	}
	
	return;
}  
  
static void gps_user_event_cb(struct bufferevent *bev, short events, void *user_data)  
{ 
	SGpsUser *user = (SGpsUser *)user_data;

	LOG_DEBUG("[Engine:%d][FD:0x%x]event callback %d", user->engine->engine_no, user->fd, events);			
      
    destroy_gps_user((SGpsUser *)user_data);
	return;
}  

static void gps_user_timer_cb(int fd, short flag, void *para)  
{ 
	SGpsUser *user = (SGpsUser *)para;
	struct timeval tv;	
	user->check_no++;
	LOG_DEBUG("[Engine:%d][FD:0x%x]update:%d check_no:%d", user->engine->engine_no, user->fd, user->update, user->check_no);			
	if (user->update) {
		user->update = 0;
		user->check_no = 0;
		return;
	}

	if (user->check_no >= MAX_CHECK_NUM) {
		LOG_DEBUG("[Engine:%d][FD:0x%x] out of timer", user->engine->engine_no, user->fd);			
		destroy_gps_user(user);
		return;
	}
	tv.tv_sec = 60*3;
	tv.tv_usec =0;	
	evtimer_add(user->event_timer, &tv);

	return;
}


SGpsUser *create_gps_user(SEngine *engine, evutil_socket_t fd)
{
	assert(engine);
	struct timeval tv;
	SGpsUser *user = (SGpsUser *)calloc(sizeof(SGpsUser), 1);
	if (!user) {
		LOG_ERROR("[Engine:%d][FD:0x%x] create failure", engine->engine_no, fd);			
		return NULL;
	}
	user->bev_socket = bufferevent_socket_new(engine->base, fd, BEV_OPT_CLOSE_ON_FREE);
	if(!user->bev_socket) {
		LOG_ERROR("[Engine:%d][FD:0x%x] new bufferevent failure", engine->engine_no, fd);			
		free(user);
		return NULL;
	}

	user->event_timer = evtimer_new(engine->base, gps_user_timer_cb, user);
	if (!user->event_timer) {
		LOG_ERROR("[Engine:%d][FD:0x%x] evtime_new failure", engine->engine_no, fd);			
		bufferevent_free(user->bev_socket);
		free(user);
		return NULL;
	}

	user->engine = engine;
	user->check_no = 0;
	user->status = USER_CONNECT;
	user->update = 0; /*false*/
	user->fd = fd;
	memset(user->device_id,NULL,8);

	
	tv.tv_sec = 60*3;
	tv.tv_usec =0;	
	evtimer_add(user->event_timer, &tv);
    bufferevent_setcb(user->bev_socket, gps_user_read_cb, gps_user_write_cb, gps_user_event_cb, user);  
    bufferevent_enable(user->bev_socket, EV_READ);  	

	LOG_DEBUG("[Engine:%d][FD:0x%x] create successfully", engine->engine_no, fd);			

	return user;
	
}
void destroy_gps_user(SGpsUser * user)
{
	assert(user);
	assert(user->event_timer);
	assert(user->bev_socket);
	LOG_DEBUG("[Engine:%d][FD:0x%x] destroy", user->engine->engine_no, user->fd);
	bufferevent_free(user->bev_socket);
	evtimer_del(user->event_timer);
	free(user);	

	return;
}
