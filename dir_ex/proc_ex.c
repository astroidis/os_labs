#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>


#define BUFSIZE 4000
#define ROOTPATH "/proc/"


void get_info_from_proc(char *filename, char *fieldname, char *dest){
    int fd;
    char buffer[BUFSIZE];
    size_t bytes_read;
    char path[30] = ROOTPATH;
    char exp_to_search[30];
    char *match;

    strcat(path, filename);

    if (isdigit(filename[0])){
        if (!strcmp(fieldname, "Name:") || !strcmp(fieldname, "Pid:")
            || !strcmp(fieldname, "Uid:")){
                strcat(path, "/status");
        }
        else if (!strcmp(fieldname, "cmdline")){
            strcat(path, "/cmdline");
        }
    }

    fd = open(path, O_RDONLY);
    bytes_read = read(fd, buffer, BUFSIZE);
    close(fd);

    if (bytes_read == 0 || bytes_read == -1 || bytes_read == BUFSIZE){
        return;
    }

    buffer[BUFSIZE] = '\0';

    if (!strcmp(fieldname, "cmdline")){
        strcpy(dest, buffer);
    }
    else
    {
      match = strstr(buffer, fieldname);
        if (match == NULL){
            return;
        }

        strcpy(exp_to_search, fieldname);
        strcat(exp_to_search, " %s");
        sscanf(match, exp_to_search, dest);
    }
}


int main(){
    DIR *dp;
    struct dirent *dirp;
    char version[50];
    char mem_total[50];
    char mem_free[50];
    char load_avg[50];
    char cpu[20];
    char name[10];
    char pid[10];
    char uid[10];
    char ter[1024];

    get_info_from_proc("version", "Linux version", version);
    printf("Linux version: %s\n", version);

    get_info_from_proc("cpuinfo", "cpu MHz\t\t:", cpu);
    printf("CPU clock frequency: %s\n", cpu);

    get_info_from_proc("loadavg", "", load_avg);
    printf("Load average: %s\n", load_avg);

    get_info_from_proc("meminfo", "MemTotal:", mem_total);
    printf("Total amount of RAM: %s\n", mem_total);

    get_info_from_proc("meminfo", "MemFree:", mem_free);
    printf("Free amount of RAM: %s\n", mem_free);

    dp = opendir(ROOTPATH);
    if (dp == NULL){
        perror("opendir");
        return 1;
    }

    while ((dirp = readdir(dp)) != NULL){
        if (isdigit(dirp->d_name[0])){
            get_info_from_proc(dirp->d_name, "Name:", name);
            get_info_from_proc(dirp->d_name, "Pid:", pid);
            get_info_from_proc(dirp->d_name, "Uid:", uid);
            get_info_from_proc(dirp->d_name, "cmdline", ter);

            printf("\nProcess id: %s\n", pid);
            printf("Command name: %s\n", name);
            printf("User id: %s\n", uid);
            printf("Terminal: %s\n", ter);
        }
    }

    closedir(dp);

    return 0;
}
