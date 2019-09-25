#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/utsname.h>
#include<unistd.h>
void display(char * home){
    struct utsname name;
    uname(&name);int flag=1;
    char pwd[1000];getcwd(pwd,1000);
    for(int i=0;i<strlen(home);i++){
        if(pwd[i]!=home[i]){
            flag=0;
        }
    }
    if(strlen(pwd)<strlen(home)){
        flag = 0;
    }
    char correctPWD[1000]="";
    if(flag){
        correctPWD[0]='~';int temp=1;
        for(int i=strlen(home);i<strlen(pwd);i++){
            correctPWD[temp++]=pwd[i];
        }
    }
    else{
        strcpy(correctPWD,pwd);
    }
    printf("<%s@%s:%s>",getenv("USER"),name.nodename,correctPWD);
    char buffer[100];
    sprintf(buffer,"<%s@%s:%s>",getenv("USER"),name.nodename,correctPWD);
}