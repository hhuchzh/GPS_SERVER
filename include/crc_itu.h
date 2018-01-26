#ifndef __CRC_ITU_H__
#define __CRC_ITU_H__

#include <stdio.h>

unsigned short get_crc_16 (const unsigned char *pData,int nLength);
int is_crc16_good(const unsigned char *pData,int nLength, unsigned short crc);

#endif
