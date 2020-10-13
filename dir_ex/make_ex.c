#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main(){
    if (mkdir("test1", 0644) == -1){
        perror("mkdir(test1)");
        return -1;
    }
    else{
        printf("test1 created successfully\n");
    }

    if (mkdir("test2", 0644) == -1){
        perror("mkdir(test2)");
        return -1;
    }
    else{
        printf("test2 created successfully\n");
    }

    if (rmdir("test2") == -1){
        perror("rmdir(test2)");
        return -1;
    }
    else{
        printf("test2 removed successfully\n");
    }

    return 0;
}
