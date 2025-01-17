#include "PNF.hpp"

void fill_message(PNF_READY &message)
{
    message.version_info                    = 1;    // Inverse order to call sizeof() later

    message.message_header.termination_type = 0x01;
    message.message_header.phy_id           = 0;
    message.message_header.message_id       = 7;    // Arbitrary, the actual ID was not defined in (provied) SCF 225
    message.message_header.length           = sizeof(message.version_info);

    message.nfapi_header.segment_length     = message.message_header.length + sizeof(message.message_header);
    message.nfapi_header.more               = false;
    message.nfapi_header.segment_number     = 0;
    message.nfapi_header.sequence_number    = 0;
    message.nfapi_header.transit_timestamp  = 0;    // Defined as 0 in the spec
}

int main(int argc, char* argv[])
{
    int client_fd = 0;
    const char* server_ip = NULL;
    int server_port = 0;

    if(argc == 3) {     // User provided IP and PORT
        server_ip = argv[1];
        server_port = atoi(argv[2]);
        if(server_port < 1 || server_port > 65535) {
            printf("Invalid port number (%d). Valid values are between 1 and 65535.\n", server_port);
            return 1;
        }
    }

    else {    // User provided invalid number of arguments
        printf("Usage: %s [SERVER IP ADDRESS] [SERVER PORT]\n", argv[0]);
        return 2;
    }

    client_fd = socket(ADDR_FAMILY, SOCK_TYPE, PROTO);
    if(client_fd == -1) {
        perror("socket");
        return 3;
    }

    struct sockaddr_in peer_addr;
    memset(&peer_addr, 0, sizeof(struct sockaddr_in));
    peer_addr.sin_family = ADDR_FAMILY;
    peer_addr.sin_port = htons(server_port);
    if(inet_pton(AF_INET, server_ip, &(peer_addr.sin_addr)) != 1) {
        printf("Error converting IP address (%s) to sockaddr_in structure\n", server_ip);
        return 4;
    }

    printf("Connecting...\n");

    if(connect(client_fd, (struct sockaddr*)&peer_addr, sizeof(peer_addr)) == -1) {
        perror("connect");
        return 5;
    }

    printf("OK\n");

    char buf[20];
    printf("Sending message\n");

    memset(buf, 0, sizeof(buf));
    PNF_READY message;
    fill_message(message);
    int offset = 0;
    memcpy(buf, (const unsigned char*)&message, sizeof(message));

    if(send(client_fd, &buf, sizeof(buf), 0) == -1) {
        perror("send");
        return 6;
    }
    
    printf("Closing...\n");
    if(close(client_fd) == -1) {
        perror("close");
        return 7;
    }

    return 0;
}