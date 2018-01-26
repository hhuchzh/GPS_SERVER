#include "logger.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define CATEGORY_NAME "logger"
static log4c_category_t *log_category = NULL;

int create_logger(void)
{
    log4c_init();
    log_category = log4c_category_get(CATEGORY_NAME);
 	if (!log_category) {
		return 0;
	}
	
    return 1;
}

void log_message(int priority ,const char *file, int line, const char *fun,const char *fmt , ...)
{
    char new_fmt[2048];
    const char * head_fmt = "[file:%s, line:%d, function:%s]";
    va_list ap;
    int n;

    assert(log_category != NULL);
    n = snprintf(new_fmt, 2048, head_fmt , file , line , fun);
    strcat(new_fmt + n , fmt);

    va_start(ap , fmt);
    log4c_category_vlog(log_category , priority, new_fmt , ap);
    va_end(ap);
}

void destroy_logger()
{
    log4c_fini();
}
