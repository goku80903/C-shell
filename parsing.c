#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/utsname.h>
#include<unistd.h>
#include<dirent.h>
void parsing(char * p,char * history_location){
    char *input = NULL;
    ssize_t b = 0;
    getline(&input,&b,stdin);
    if(input[0]=='\n'){
        return ;
    }
    else{
        char * many = strtok(input,";");
        char ** functions = (char **)malloc(100 * sizeof(char *));
        for(int i=0;i<10;i++){
            functions[i] = (char *)malloc(sizeof(char));
        }
        int t=0;
        while (many)
        {
            strcpy(functions[t++],many);
            many = strtok(NULL,";");
        }
        for(int i=t;i<10;i++){
            strcpy(functions[i],"");
        }
        t=0;
        for(int i=0;i<10;i++){
            if(strcmp(functions[i],"")!=0){
                t++;
            }
        }
        for(int i=0;i<t;i++){
            char * parse = strtok(functions[i]," ");
            char ** split = (char**)malloc(100 * sizeof(char *));
            for(int i=0;i<10;i++){
                split[i] = (char *)malloc(sizeof(char));
            }
            int temp=0;
            while (parse)
            {
                strcpy(split[temp++],parse);
                parse = strtok(NULL," ");
            }
            for(int i=temp;i<10;i++){
                strcpy(split[i],"");
            }
            writehistory(split,history_location);
            if(strcmp(split[0],"ls\n")==0 | strcmp(split[0],"ls")==0){
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
            else if(strcmp(split[0],"history\n")==0 | strcmp(split[0],"history")==0){
                history(split,history_location);
            }
            else{
                execute(split);
            }
        }
    }
}