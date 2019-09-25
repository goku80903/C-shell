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
void redirect(void ** split,int input,int output,char * p,char * hl){
    int first,append=0;// =0 for input and =1 for output
    if(strcmp(split[output],">>\n")==0 || strcmp(split[output],">>")==0){
        append=1;
    }
    if(input < output && input!=0 || output == 0){
        first=0;
    }
    else if(output < input && output!=0 || input == 0){
        first=1;
    }
    char ** function1=(char **)malloc(sizeof(char *)*10);
    char ** function2=(char **)malloc(sizeof(char *)*10);
    char ** function3=(char **)malloc(sizeof(char *)*10);
    for(int i=0;i<10;i++){
        function1[i]=(char *)malloc(sizeof(char));
        function2[i]=(char *)malloc(sizeof(char));
        function3[i]=(char *)malloc(sizeof(char));
    }
    int arr[2];
    if(input<output){
        arr[0]=input;
        arr[1]=output;
    }
    else{
        arr[0]=output;
        arr[1]=input;
    }
    if(arr[0]==0){
        arr[0]=arr[1];
        arr[1]=9;
    }
    int temp1=0,temp2=0,temp3=0;
    for(int i=0;i<10;i++){
        if(i<arr[0]){
            strcpy(function1[temp1++],split[i]);
        }
        else if(arr[0]<i && i<arr[1]){
            strcpy(function2[temp2++],split[i]);
        }
        else if(i>arr[1]){
            strcpy(function3[temp3++],split[i]);
        }
    }
    for(int i=temp1;i<10;i++){
        strcpy(function1[i],"");
    }
    for(int i=temp2;i<10;i++){
        strcpy(function2[i],"");
    }
    for(int i=temp3;i<10;i++){
        strcpy(function3[i],"");
    }
    if(first==1 && input==0){
        int out;
        if(append==0)
            out = open(function2[0] , O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else
            out = open(function2[0] , O_APPEND|O_WRONLY | O_CREAT , 0644);
        if(strcmp(function1[0],"cd")==0||strcmp(function1[0],"cd\n")==0){
            changeDIR(function1[1],p);
            return;
        }
        int pid = fork();
        if(pid==0){
            dup2(out,1);
            execute(function1);
            exit(0);
        }
        else{
            wait(NULL);
        }
    }
    else if(first==0 && output==0){
        if(strcmp(function1[0],"cd")==0||strcmp(function1[0],"cd\n")==0){
            changeDIR(function1[1],p);
            return;
        }
        int in = open(function2[0] , O_RDONLY);
        if(in<0){
            perror("");
            return;
        }
        int pid = fork();
        if(pid==0){
            dup2(in,0);
            execute(function1);
            exit(0);
        }
        else{
            wait(NULL);
        }
    }
    else if(first==1 && input>0){
        int out;
        if(append==0)
            out = open(function2[0] , O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else
            out = open(function2[0] , O_APPEND | O_WRONLY | O_CREAT , 0644);
        int in = open(function3[0] , O_RDONLY);
        if(strcmp(function1[0],"cd")==0||strcmp(function1[0],"cd\n")==0){
            changeDIR(function1[1],p);
            return;
        }
        int pid = fork();
        if(pid==0){
            dup2(out,1);
            execute(function1);
            exit(0);
        }
        else{
            wait(NULL);
        }
    }
    else if(first==0 && output>0){
        int in = open(function2[0] , O_RDONLY);
        int out;
        if(append==0)
            out = open(function3[0] , O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else
            out = open(function3[0] , O_APPEND| O_WRONLY | O_CREAT , 0644);
        if(strcmp(function1[0],"cd")==0||strcmp(function1[0],"cd\n")==0){
            changeDIR(function1[1],p);
            return;
        }
        int pid = fork();
        if(pid==0){
            dup2(in,0);
            dup2(out,1);
            execute(function1);
            exit(1);
        }
        else{
            wait(NULL);
        }
    }
}