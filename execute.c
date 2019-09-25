#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/utsname.h>
#include<unistd.h>
#include<dirent.h>
#include <sys/types.h>
#include<sys/wait.h>
#include<signal.h>
#include<fcntl.h> 
#include<sys/types.h>
#include<sys/stat.h>
void execute(char ** split){
    int temp=0;
    for(int i=0;i<10;i++){
        if(strlen(split[i])!=0){
            temp++;
        }
    }
    char ** process = (char **)malloc(temp*sizeof(char *));
    for(int i=0;i<=temp;i++){
        process[i]=(char *)malloc(100*sizeof(char));
    }
    for(int i=0;i<temp;i++){
        strcpy(process[i],split[i]);
        int t = strlen(process[i]);
        if(process[i][t-1]=='\n')
            process[i][t-1]='\0';
    }
    int is_background=0;
    if(strcmp(process[temp-1],"&")==0){
        is_background=1;
        process[temp-1]=NULL;
    }
    process[temp]=NULL;
    int status = 0;
    pid_t child = fork();
    if(!is_background){
        if(child == 0){
            if(execvp(process[0],process)<0){
                perror("");
            }
        }
        else{
            waitpid(child, &status, 0);
        }
    }
    else{
        if(child==0){
            int sub;
            pid_t grandchild = fork();
            if(grandchild==0){
                if(execvp(process[0],process)<0){
                    perror("");
                }
            }
            else{
                char * path = process[0]; 
                waitpid(grandchild,&sub,0);
                printf("\n%s with pid %d exited ",path,grandchild-1);
                int local = waitpid(grandchild,&sub,1);
                if(WIFEXITED(sub)){
                    printf("%s\n",strerror(WEXITSTATUS(sub)));
                }
                else{
                    printf("abrupt\n");
                }
            }
        }
        else{
            printf("%d\n",child);
        }
    }
    return;
}