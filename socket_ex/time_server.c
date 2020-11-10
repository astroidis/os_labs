/* Server sends to client a datagram with current time */

#include "socket_ex.h"
#include <time.h>

int main(){
    // create server socket
    int sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sfd == -1)
        errorExit("socket");

    // set sockaddr_un structure
    if (remove(SOCK_PATH) == -1 && errno != ENOENT)
        errorExit("remove");

    struct sockaddr_un servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sun_family = AF_UNIX;
    strncpy(servaddr.sun_path, SOCK_PATH, sizeof(servaddr.sun_path)-1);

    // bind socket to address
    socklen_t len = (socklen_t) sizeof(struct sockaddr_un);
    if (bind(sfd, (struct sockaddr *) &servaddr, len) == -1)
        errorExit("bind");

    for (;;){
        struct sockaddr_un claddr;
        ssize_t bytes = recvfrom(sfd, 0, 0, 0,
                                 (struct sockaddr *) &claddr, &len);
        if (bytes == -1)
            errorExit("recvfrom");

        time_t timer = time(0);
        struct tm *dt = localtime(&timer);
        char buf[BUF_SIZE];
        strftime(buf, BUF_SIZE, "%H:%M:%S %A %d.%m.%Y", dt);
        if (sendto(sfd, buf, BUF_SIZE, 0,
                   (struct sockaddr *) &claddr, len) == -1)
        {
            errorExit("sendto");
        }

    }
}
