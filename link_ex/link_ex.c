#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

int main(){
    struct stat buf;
    if (stat("link_ex.c", &buf) == -1){
        perror("stat");
        return -1;
    }
    printf("link_ex.c\n\tindex: %lu\n\tlinks: %lu\n",
           buf.st_ino, buf.st_nlink);

    printf("\nCreating new link...\n");

    if (link("link_ex.c", "newlink") == -1){
        perror("link");
        return -1;
    }

    if (stat("link_ex.c", &buf) == -1){
        perror("stat");
        return -1;
    }
    printf("link_ex.c\n\tindex: %lu\n\tlinks: %lu\n",
           buf.st_ino, buf.st_nlink);


    if (stat("newlink", &buf) == -1){
        perror("stat");
        return -1;
    }
    printf("newlink.c\n\tindex: %lu\n\tlinks: %lu\n",
           buf.st_ino, buf.st_nlink);


    printf("Removing link...\n");
    if (unlink("newlink") == -1){
        perror("unlink");
        return -1;
    }

    if (stat("link_ex.c", &buf) == -1){
        perror("stat");
        return -1;
    }
    printf("link_ex.c\n\tindex: %lu\n\tlinks: %lu\n",
           buf.st_ino, buf.st_nlink);

    return 0;
}
