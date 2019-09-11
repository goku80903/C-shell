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
void pinfo(char ** split){
    for(int i=0;i<10;i++){
        int t=strlen(split[i]);
        if(split[i][t-1]=='\n'){
            split[i][t-1]='\0';
        }
    }
    int pid;
    if(strcmp(split[1],"")==0){
        pid=getpid();
    }
    else{
        pid=atoi(split[1]);
        if(kill(pid,0)!=0){
            if(errno == ESRCH){
                perror("");
                return;
            }    
        }
    }
    printf("pid -- %d\n",pid);
    char status[1000],p[1000];
    sprintf(status , "/proc/%d/status",pid);
    sprintf(p , "/proc/%d/exe",pid);
    int status_file = open(status,O_RDONLY);
    read(status_file,status,1000);
    char process_status[3];int mem=0;
    for (int i = 0; i < 996; i++)
    {
        if(status[i]=='S' && status[i+1]==' '){
            process_status[0]='S';process_status[1]='\0';
        }
        else if(status[i]=='R' && status[i+1]==' '){
            process_status[0]='R';process_status[1]='\0';
        }
        else if(status[i]=='Z' && status[i+1]==' '){
            process_status[0]='Z';process_status[1]='\0';
        }
        else if(status[i]=='S' && status[i+1]=='+'){
            process_status[0]='S';process_status[1]='+';process_status[2]='\0';
        }
        if(status[i]=='V' && status[i+1]=='m' && status[i+2]=='S' && status[i+3]=='i' && status[i+4]=='z'){
            mem = i;
        }
    }
    printf("Proess Status -- %s\n",process_status);
    char memory[100];mem+=7;
    int temp=0;
    for(int i=mem;i<999;i++){
        if(status[i]=='\n'){
            break;
        }
        else if(status[i]<'0'|status[i]>'9'){
            continue;
        }
        memory[temp++]=status[i];
    }
    memory[temp]='\0';
    printf("memory -- %s\n",memory);
    char path[100];
    ssize_t len = readlink(p,path,sizeof(path)-1);
    path[len]='\0';
    printf("executable -- %s\n",path);
}