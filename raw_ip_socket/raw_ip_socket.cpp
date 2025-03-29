#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <arpa/inet.h>
#include <net/if.h>
#include <netinet/ip.h>

int main()
{
    int sock_fd = socket(AF_PACKET, SOCK_RAW, IPPROTO_RAW);
    if (sock_fd < 0) {
        perror("create raw socket FAILED!\r\n");
        return -1;
    }

    struct sockaddr_in dest_addr;
    char packet[sizeof(struct iphdr) + 20];


    return 0;
}
