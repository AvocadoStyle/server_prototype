#ifndef __MESSAGE_PROTOCOL_H__
#define __MESSAGE_PROTOCOL_H__


#include "Server.h"

#define MESSAGE_SIZE 6

//#pragma pack(push, 1)
struct Message {
	uint16_t code;
	uint32_t size;
};

struct st {
	Message m;
	char buff[sizeof(m)];
};

union uni {
	Message m;
	char buff[sizeof(m)];
};

#endif
