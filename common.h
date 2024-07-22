#include <stdio.h>
#include <string.h>
#include <unistd.h>		//for close()
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
#include <arpa/inet.h>	//for inet_ntop()


const int SERVER_PORT = 22222;
const int ADDR_FAMILY = AF_INET;
const int SOCK_TYPE = SOCK_STREAM;
const int PROTO = IPPROTO_SCTP;
const int SERVER_LISTEN_QUEUE_SIZE = 10;