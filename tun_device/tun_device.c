#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/if_tun.h>
#include <linux/if.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <pthread.h>

#define TUN_DEV_PATH "/dev/net/tun"
#define TUN_IP "192.168.33.1/24"
#define BUFFER_SIZE 8192

int create_tun_device(void)
{
    // 打开tun设备
    int fd = open(TUN_DEV_PATH, O_RDWR);
    if (fd < 0) {
        perror("open tun device FAILED!\r\n");
        return -1;
    }

    // 配置tun设备名字和类型
    struct ifreq if_req;
    memset(&if_req, 0, sizeof(if_req));
    if_req.ifr_ifru.ifru_flags = IFF_TUN | IFF_NO_PI;
    strncpy(if_req.ifr_ifrn.ifrn_name, "tun0", IFNAMSIZ);
    if (ioctl(fd, TUNSETIFF, (void *)&if_req) < 0) {
        perror("ioctl to tun fd FAILED!\r\n");
        close(fd);
        return -1;
    }

    return fd;
}

// TODO: do not use system
// TODO: check result
void configure_tun_device()
{
    system("ip addr add " TUN_IP " dev tun0");
    usleep(500 * 1000);
    system("ip link set tun0 up");
}

int main()
{
    int tun_fd = create_tun_device();
    printf("tun fd: [%d]\r\n", tun_fd);
    if (tun_fd < 0) {
        return -1;
    }
    configure_tun_device();

    int r_count = 0;
    int w_count = 0;
    char buffer[BUFFER_SIZE] = {0};

    while (1)
    {
        r_count = read(tun_fd, (void *)buffer, sizeof(buffer));
        printf("read [%d] bytes from tun device!\r\n", r_count);
    }

    return 0;
}