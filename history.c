#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/utsname.h>
#include<unistd.h>
#include<dirent.h>
#include <sys/types.h>
#include<fcntl.h>
void history(char ** split,char * path){
    int fd = open(path,O_RDONLY);
    if(fd<0){
        perror("HISTORY ERROR");
    }
    else{
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
        int total_num=10;
        if(strcmp(split[1],"")!=0){
            total_num=atoi(split[1]);
            if(total_num>10){
                printf("NOT MORE THAN 10\n");
                return;
            }
        }
        int count =1;
        char buffer[10000];
        int size = lseek(fd,0,SEEK_END);
        lseek(fd,0,SEEK_SET);
        read(fd,buffer,size);
        for(int i=0;i<size-1;i++){
            if(buffer[i]=='\n')
                count++;
        }
        int present=1;t=0;char output[1000];
        for(int i=0;i<size-1;i++){
            if(count-present<total_num){
                output[t++]=buffer[i];
            }
            if(buffer[i]=='\n'){
                present++;
            }
        }
        output[t]='\0';
        printf("%s\n",output);
    }
}