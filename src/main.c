#include "listener.h"
#include <stdio.h>
#include <event2/thread.h>
#include "crc_itu.h"
#include "msg.h"
#include "logger.h"


unsigned char msg[18] = {0x78, 0x78, 0x0D, 0x01, 0x01, 0x23, 0x45, 0x67, 0x89, 0x01, 0x23, 0x45, 0x00, 0x01, 0x8C, 0xDD, 0x0D, 0x0A};
unsigned char resp_msg[100];

int main(int argc, char **argv)
{
	create_logger();
	LOG_INFO("BUS Server Start Now....");
	evthread_use_pthreads();
	SListener *bus_server = create_listener(5900);
#if 0 //TEST
	unsigned crc = get_crc_16(&msg[2], 12);
	unsigned good = is_crc16_good(&msg[2], 12, (unsigned short)msg[14] << 8 | msg[15]);
	unsigned seq = get_init_req_seq(msg, 18);
	generate_msg_init_resp(resp_msg, 100, seq);
	printf("crc value %x, crc good %d\n", crc, good);
#endif
	run_listener(bus_server);
	return 0;	
}
