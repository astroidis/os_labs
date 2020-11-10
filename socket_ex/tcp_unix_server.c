/* Server reads data from client and ouputs it to stdout */

#include "socket_ex.h"

int main(){
    // create new tcp-socket in unix domain
    int sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sfd == -1)
        errorExit("socket");

    // remove socket path if it already exists
    if (remove(SOCK_PATH) == -1 && errno != ENOENT)
        errorExit("remove");

    // set sockaddr_un structure
    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path)-1);

    // bind socket to address
    if (bind(sfd, (struct sockaddr *) &addr, sizeof(addr)) == -1)
        errorExit("bind");

    // make listening socket
    if (listen(sfd, BACKLOG) == -1)
        errorExit("listen");

    // handle client connections
    for (;;){
        // accept new connection
        int csfd = accept(sfd, 0, 0);
        if (csfd == -1)
            errorExit("accept");

        // copy data from socket to stdout
        ssize_t bytesRead;
        char buf[BUF_SIZE];
        while ((bytesRead = read(csfd, buf, BUF_SIZE)) > 0){
            if (write(STDOUT_FILENO, buf, bytesRead) != bytesRead)
                fatal("Failed write");
        }

        if (bytesRead == -1)
            errorExit("read");

        if (close(csfd) == -1)
            errorExit("close");
    }

    return 0;
}
