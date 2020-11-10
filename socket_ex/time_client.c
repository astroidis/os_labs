/* Client connects to server and receive server current time */

#include "socket_ex.h"

#define CLIENT_PATH "/tmp/sock_client"

int main(){
    // create new socket
    int sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sfd == -1)
        errorExit("socket");

    // set client address
    if (remove(CLIENT_PATH) == -1 && errno != ENOENT)
        errorExit("remove");

    struct sockaddr_un claddr;
    socklen_t len = sizeof(claddr);
    memset(&claddr, 0, len);
    claddr.sun_family = AF_UNIX;
    strncpy(claddr.sun_path, CLIENT_PATH, sizeof(claddr.sun_path)-1);

    if (bind(sfd, (struct sockaddr *) &claddr, len) == -1)
        errorExit("bind");

    // set server address
    struct sockaddr_un servaddr;
    memset(&servaddr, 0, len);
    servaddr.sun_family = AF_UNIX;
    strncpy(servaddr.sun_path, SOCK_PATH, sizeof(servaddr.sun_path)-1);

    if (sendto(sfd, "", 0, 0, (struct sockaddr *) &servaddr, len) == -1)
        errorExit("sendto");

    // receive message from server and print it
    char buf[BUF_SIZE];
    ssize_t bytes = recvfrom(sfd, buf, BUF_SIZE, 0, 0, 0);
    if (bytes == -1)
        errorExit("recvfrom");

    buf[bytes] = 0;
    printf("%s\n", buf);

    remove(CLIENT_PATH);
    return 0;
}
