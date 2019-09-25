#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/utsname.h>
#include<unistd.h>
#include<dirent.h>
#include<fcntl.h>
#include<limits.h>
#include<signal.h>
#include<errno.h>
void Setenv(char ** split){
    int count=0;
    for(int i=0;i<10;i++)
    {
        if(strcmp(split[i],"")!=0){
            count++;
        }
    }
    if(count==1 || count >3){
        printf("Invalid arguments\n");
        return;
    }
    if(setenv(split[1],split[2],1)<0){
        perror("");
    }
}