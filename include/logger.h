#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "log4c.h"


#include <string.h>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)


#define LOG_PRI_FATAL		LOG4C_PRIORITY_FATAL
#define LOG_PRI_ERROR 		LOG4C_PRIORITY_ERROR
#define LOG_PRI_WARN 		LOG4C_PRIORITY_WARN
#define LOG_PRI_NOTICE 		LOG4C_PRIORITY_NOTICE
#define LOG_PRI_INFO		LOG4C_PRIORITY_INFO
#define LOG_PRI_DEBUG 		LOG4C_PRIORITY_DEBUG
#define LOG_PRI_TRACE 		LOG4C_PRIORITY_TRACE

int create_logger(void);
void log_message(int priority ,const char *file, int line, const char *fun,const char *fmt , ...);
void destroy_logger(void);


#define LOG_FATAL(fmt,args...)\
    log_message(LOG_PRI_FATAL,__FILENAME__ , __LINE__ , __FUNCTION__ , fmt , ##args)
#define LOG_ERROR(fmt , args...)\
    log_message(LOG_PRI_ERROR,__FILENAME__ , __LINE__ , __FUNCTION__ , fmt, ##args)
#define LOG_WARN(fmt, args...)\
    log_message(LOG_PRI_WARN,__FILENAME__ , __LINE__ , __FUNCTION__ , fmt , ##args)
#define LOG_NOTICE(fmt , args...)\
    log_message(LOG_PRI_NOTICE,__FILENAME__ , __LINE__ , __FUNCTION__ , fmt , ##args)
#define LOG_INFO(fmt,args...)\
    log_message(LOG_PRI_INFO,__FILENAME__ , __LINE__ , __FUNCTION__ , fmt , ##args)
#define LOG_DEBUG(fmt , args...)\
    log_message(LOG_PRI_DEBUG,__FILENAME__ , __LINE__ , __FUNCTION__ , fmt , ##args)
#define LOG_TRACE(fmt,args...)\
    log_message(LOG_PRI_TRACE, __FILENAME__ , __LINE__ , __FUNCTION__ , fmt ,##args)

#endif
