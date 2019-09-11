#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/utsname.h>
#include<unistd.h>
#include<dirent.h>
#include <sys/types.h>
#include<fcntl.h>
void writehistory(char ** split,char * path){
    int fd = open(path,O_CREAT | O_APPEND | O_WRONLY,0744);
    int temp=0;
    for(int i=0;i<10;i++){
        if(strcmp(split[i],"")!=0){
            temp++;
        }
    }
    int t = strlen(split[temp-1]);
    if(split[temp-1][t-1]=='\n'){
        split[temp-1][t-1]='\0';
    }
    for(int i=0;i<temp;i++){
        if(i<temp-1){
            write(fd,split[i],strlen(split[i]));
            write(fd," ",strlen(" "));
        }
        else{
            write(fd,split[i],strlen(split[i]));
            write(fd,"\n",strlen("\n"));
        }
    }
}
