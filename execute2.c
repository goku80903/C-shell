#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/utsname.h>
#include<unistd.h>
#include<dirent.h>
#include<readline/readline.h>
#include<readline/history.h>
void execute2(char ** split,char * p,char * history_location){
    int count=0;
    for(int i=0;i<100;i++){
        if(strcmp(split[i],"")!=0){
            count++;
        }
    }
    int input=0,output=0,piping=0;
    for(int i=0;i<count;i++){
        if(strcmp(split[i],">")==0 || strcmp(split[i],">\n")==0 || strcmp(split[i],">>\n")==0 || strcmp(split[i],">>")==0){
            output=i;
        }
        else if(strcmp(split[i],"<")==0 || strcmp(split[i],"<\n")==0){
            input=i;
        }
        else if(strcmp(split[i],"|")==0 || strcmp(split[i],"|\n")==0){
            piping++;
        }
    }
    writehistory(split,history_location);
    if(piping){
        Piping(split);
    }
    else if(input || output){
        redirect(split,input,output,p,history_location);
    }
    else if(strcmp(split[0],"ls\n")==0 | strcmp(split[0],"ls")==0){
        ls(split,p);
    }
    else if(strcmp(split[0],"cd\n")==0 | strcmp(split[0],"cd")==0){
        changeDIR(split[1],p);
    }
    else if(strcmp(split[0],"pwd\n")==0 | strcmp(split[0],"pwd")==0){
        pwd();
    }
    else if(strcmp(split[0],"echo")==0){
        echo(split);
    }
    else if(strcmp(split[0],"pinfo\n")==0 | strcmp(split[0],"pinfo")==0){
        pinfo(split);
    }
    else if(strcmp(split[0],"setenv\n")==0 | strcmp(split[0],"setenv")==0){
        Setenv(split);
    }
    else if(strcmp(split[0],"unsetenv\n")==0 | strcmp(split[0],"unsetenv")==0){
        Unsetenv(split);
    }
    else if(strcmp(split[0],"history\n")==0 | strcmp(split[0],"history")==0){
        history(split,history_location);
    }
    else if(strcmp(split[0],"quit\n")==0 | strcmp(split[0],"quit")==0){
        exit(1);
    }
    else{
        execute(split);
    }
}