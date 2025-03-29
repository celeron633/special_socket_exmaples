#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int ret = 0;
    struct sockaddr_in send_addr;
    send_addr.sin_family = AF_INET;
    send_addr.sin_addr.s_addr = INADDR_BROADCAST;
    send_addr.sin_port = htons(8083);

    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    connect(sock_fd, (struct sockaddr *)&send_addr, sizeof(send_addr));

    // allow broadcast
    int en_broadcast = 1;
    ret = setsockopt(sock_fd, SOL_SOCKET, SO_BROADCAST, &en_broadcast, sizeof(en_broadcast));
    if (ret < 0) {
        perror("setsockopt error!\r\n");
        return -1;
    }


    int i = 0;
    char buf[16] = {0};
    // int ret = 0;
    while (1) {
        sprintf(buf, "%d", i);
        i++;
        // ret = send(sock_fd, buf, strlen(buf)+1, 0);
        printf("sending broadcast...buf:[%s]\r\n", buf);
        ret = sendto(sock_fd, buf, strlen(buf)+1, 0, (struct sockaddr *)&send_addr, sizeof(send_addr));
        if (ret < 0) {
            perror("send error!\r\n");
            return -1;
        }
        sleep(1);
    }

    return 0;
}