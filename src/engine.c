#include "engine.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "logger.h"
#include "occi.h"

static string name = "youtu";
static string pass = "QWE123asd";
static string srvName = "121.40.19.77:1521/orcl";

static void *engine_thr_fn(void *arg)
{
	SEngine *engine = (SEngine *)arg;
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 10 * 1000;	
	LOG_INFO("engine no=%d tid=0x%x", engine->engine_no, (int)engine->tid);
	engine->status = ENGINE_STATUS_RUN;
	while (engine->status == ENGINE_STATUS_RUN) {
		event_base_loopexit(engine->base, &tv) ;
		event_base_dispatch(engine->base);
	}
	engine->status = ENGINE_STATUS_STOPPED;
	LOG_INFO("exit thead,engine no=%d tid=0x%x", engine->engine_no, (int)engine->tid);

	return NULL;
}

SEngine *create_engine(int no)
{
	SEngine *engine = (SEngine *)calloc(sizeof(SEngine), 1);
	if (!engine) {
		LOG_ERROR("create engine failure");
		return NULL;
	}
	engine->base = event_base_new();
	if (!engine->base) {
		LOG_ERROR("new event base failure");
		return NULL;
	}

	engine->engine_no = no;
	engine->status = ENGINE_STATUS_INIT;

	/*Fix me*/
	
    engine->env = Environment::createEnvironment(Environment::DEFAULT);
	try{
    	   engine->con = engine->env->createConnection(name, pass, srvName);
	} catch (SQLException& ex){
            LOG_DEBUG("chenz create Connection failed");
     	    LOG_ERROR("chenz %s\n",ex.getMessage().c_str());
            exit(EXIT_FAILURE);
	}

    try{
        engine->stmt = engine->con->createStatement();
   	}catch (SQLException& ex) {
     	LOG_ERROR("chenz %s\n",ex.getMessage().c_str());
	    exit(EXIT_FAILURE);
   	}	

	LOG_INFO("create engine %d", no);

	return engine;
}


void run_engine(SEngine *engine)
{
	assert(engine);
	pthread_create(&engine->tid, NULL, engine_thr_fn, engine);	
}


void stop_engine(SEngine *engine)
{
	engine->status = ENGINE_STATUS_STOP;
}


int destroy_engine(SEngine *engine)
{
	assert(engine);

	if (engine->status != ENGINE_STATUS_STOPPED) {
		LOG_WARN("invalid status %d", engine->status);
		return 0;
	}

	event_base_free(engine->base);
	free(engine);
	LOG_INFO("delete");	
	return 1;
}
