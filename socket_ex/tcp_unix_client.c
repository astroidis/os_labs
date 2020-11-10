/* Client reads data from stdin and sends it to server */

#include "socket_ex.h"

int main(){
    // create new socket
    int sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sfd == -1)
        errorExit("socket");

    // set sockaddr_un structure (server address)
    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path)-1);

    // connect socket to address
    if (connect(sfd, (struct sockaddr *) &addr, sizeof(addr)) == -1)
        errorExit("connect");

    // copy data from stdio to socket
    ssize_t bytesRead;
    char buf[BUF_SIZE];
    while ((bytesRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0){
        if (write(sfd, buf, bytesRead) != bytesRead)
            fatal("Failed write");
    }

    if (bytesRead == -1)
        errorExit("read");

    close(sfd);
    return 0;
}
