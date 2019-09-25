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
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<sys/wait.h>
void Piping(char ** split){
    int count=0,p[100],it[100]={0};
    for(int i=0;i<100;i++){
        if(strcmp(split[i],"")!=0){
            count++;
        }
    }
    for(int i=0;i<100;i++){
        p[i]=count;
    }
    int temp=0;
    for(int i=0;i<count;i++){
        if(strcmp(split[i],"|")==0){
            p[temp++]=i;
        }
    }
    char *** functions=(char ***)malloc(sizeof(char **)*10);
    for(int i=0;i<10;i++){
        functions[i]=(char **)malloc(sizeof(char *)*100);
        for(int j=0;j<10;j++){
            functions[i][j]=(char *)malloc(sizeof(char)*100);
        }
    }
    temp=0;
    for(int i=0;i<count;i++){
        if(i<p[temp]){
            strcpy(functions[temp][it[temp]++],split[i]);
        }
        else{
            temp++;
        }
    }
    int pipes=0;
    for(int i=0;i<100;i++){
        if(it[i]!=0){
            pipes++;
        }
    }
    for(int i=0;i<count;i++){
        for(int j=it[i];j<10;j++){
            strcpy(functions[i][j],"");
        }
    }
    int status;
    int m[2*(pipes-1)];
    for(int i=0;i<2*(pipes-1);i+=2){
        pipe(m+i);
    }
    for(int i=0;i<pipes;i++){
        int pid=fork();
        if(pid==0){
            if(i!=0){
                dup2(m[2*i-2],0);
            }
            if(i!=pipes-1){
                dup2(m[2*i+1],1);
            }
            for(int j=0;j<2*(pipes-1);j++){
                close(m[j]);
            }
            execute(functions[i]);
            exit(1);
        }
    }
    for(int i=0;i<2*(pipes-1);i++){
        close(m[i]);
    }
    for(int i=0;i<2*(pipes-1);i++){
        wait(&status);
    }
    return;
}