#ifndef __MESSAGE_PROTOCOL_H__
#define __MESSAGE_PROTOCOL_H__




#define MESSAGE_SIZE 6

//#pragma pack(push, 1)
//struct Message {
//	uint16_t code;
//	uint32_t size;
//};
//
//struct st {
//	Message m;
//	char buff[sizeof(m)];
//};
//
//union uni {
//	Message m;
//	char buff[sizeof(m)];
//};
//
//
struct request_header {
    uint32_t user_id;
    uint8_t version;
    uint8_t op;
    uint16_t name_len;
    uint8_t filename[1024]; //need to make it dynamic
};



struct request_from_client{
    int type_head_or_payload;
    union payload {
        request_header req_head;
        uint32_t size;
        char buff_request[(sizeof(req_head) + sizeof(size))];
    };
};

//
//
//
//
//
//
//
//
//typedef struct RequestHeader
//{
//    uint32_t userId;        // User ID
//    uint8_t  version;       // Client version
//    uint8_t  op;            // Request opCode
//    uint16_t name_len;      // File name length
//    uint8_t* filename;
//}RequestHeader;
//
//typedef struct ResponseHeader
//{
//    uint8_t  version;       // Server version
//    uint16_t status;        // Status for Request
//    uint16_t name_len;      // File name length
//    uint8_t* filename;
//}ResponseHeader;
//#pragma pack(pop)
//
//typedef struct Payload {
//    uint32_t size;          // file size
//    uint8_t* payload;       // pyaload - file contant
//}Payload;
//
//typedef struct RequestMessage {
//    RequestHeader header;   // Message header
//    Payload data; // message data
//}RequestMessage;
//
//
//typedef struct ResponseMessage {
//    ResponseHeader header;   // Message header
//    Payload data; // message data
//}ResponseMessage;





#endif
