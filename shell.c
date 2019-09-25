#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/utsname.h>
#include<unistd.h>
#include<dirent.h>
#include<fcntl.h>
#include<signal.h>
void handler(int sig_num){
    signal(SIGINT,handler);
    fflush(stdout);
}
int main(void)
{
    signal(SIGINT,handler);
    char pwd[1000];
    int pid = getpid();
    char path[1000];
    sprintf(path,"/proc/%d/exe",pid);
    ssize_t len = readlink(path,pwd,sizeof(pwd)-1);
    pwd[len]='\0';int flag=0;
    for(int i=0;i<len;i++){
        if(pwd[i]=='/'){
            flag=i;
        }
    }
    for(int i=flag;i<len;i++){
        pwd[i]='\0';
    }
    char history_location[1000]="";
    sprintf(history_location,"%s/.history",pwd);
    while (1)
    {
        display(pwd); 
        parsing(pwd,history_location);
    }   
}
