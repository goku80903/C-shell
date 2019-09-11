#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/utsname.h>
#include<unistd.h>
void changeDIR(char * dest,char * pwd){
    for(int i=0;i<strlen(dest);i++){
        if(dest[i]=='\n'){
            dest[i]='\0';
        }
    }
    char actual_dest[10000];
    if(strcmp(dest,"")==0){
        if(chdir(pwd)!=0){
            perror("");
        }
    }
    else if(dest[0]=='~'){
        strcpy(actual_dest,pwd);
        strcat(actual_dest,"/");
        int temp = strlen(actual_dest);
        if(dest[1]!='\0'){
            for(int i=2;i<strlen(dest);i++){
                actual_dest[temp++]=dest[i];
            }
        }
        actual_dest[temp]='\0';
        int check = chdir(actual_dest);
        if(check < 0){
            perror("");
        }
    }
    else if(dest[0]=='/'){
        if(chdir(dest)!=0){
            perror("");
        }
    }
    else{
        getcwd(actual_dest,10000);
        strcat(actual_dest,"/");
        strcat(actual_dest,dest);
        strcat(actual_dest,"\0");
        if(chdir(actual_dest)!=0){
            perror("");
        }
    }
}