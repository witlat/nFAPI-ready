#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>


const int SERVER_PORT = 22222;
const int ADDR_FAMILY = AF_INET;
const int SOCK_TYPE = SOCK_STREAM;
const int PROTO = IPPROTO_SCTP;

struct PNF_READY {
    struct nfapi_header {
        unsigned int    segment_length      : 16;
        unsigned int    more                : 1;
        unsigned int    segment_number      : 7;
        unsigned int    sequence_number     : 8;
        unsigned int    transit_timestamp   : 32;
    } nfapi_header;
    struct message_header {
        unsigned int    termination_type    : 8;
        unsigned int    phy_id              : 8;
        unsigned int    message_id          : 16;
        unsigned int    length              : 32;
    } message_header;
    uint32_t version_info;
    // Padding ommited as it is technically the last message
};