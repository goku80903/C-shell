#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/utsname.h>
#include<unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include<grp.h>
#include<time.h>
char * acutalDEST(char * dest,char * pwd){
    for(int i=0;i<strlen(dest);i++){
        if(dest[i]=='\n'){
            dest[i]='\0';
        }
    }
    char *actual_dest = "";
    if(strcmp(dest,"")==0){
        return "./";
    }
    else if(dest[0]=='~'){
        actual_dest=pwd;
        int temp = strlen(actual_dest);
        if(dest[1]!='\0'){
        strcat(actual_dest,"/");
            for(int i=2;i<strlen(dest);i++){
                actual_dest[temp++]=dest[i];
            }
        }
        actual_dest[temp]='\0';
        return actual_dest;
    }
    else if(dest[0]=='/'){
        return dest;
    }
    else{
        char cwd[1000];
        getcwd(cwd,1000);actual_dest=cwd;
        strcat(actual_dest,"/");
        if(strcmp(dest,"")!=0){
            strcat(actual_dest,dest);
        }
        strcat(actual_dest,"\0");
        return actual_dest;
    }
}
void information(char * present){
    char value[10000]="";
    struct stat stats;
    stat(present,&stats);
    int check = S_ISDIR(stats.st_mode);
    char permissions[11];
    (S_ISDIR(stats.st_mode) == 1 )?(permissions[0]='d'):(permissions[0]='-');
    (S_IRUSR & stats.st_mode)?(permissions[1]='r'):(permissions[1]='-');
    (S_IWUSR & stats.st_mode)?(permissions[2]='w'):(permissions[2]='-');
    (S_IXUSR & stats.st_mode)?(permissions[3]='x'):(permissions[3]='-');
    (S_IRGRP & stats.st_mode)?(permissions[4]='r'):(permissions[4]='-');
    (S_IWGRP & stats.st_mode)?(permissions[5]='w'):(permissions[5]='-');
    (S_IXGRP & stats.st_mode)?(permissions[6]='x'):(permissions[6]='-');
    (S_IROTH & stats.st_mode)?(permissions[7]='r'):(permissions[7]='-');
    (S_IWOTH & stats.st_mode)?(permissions[8]='w'):(permissions[8]='-');
    (S_IXOTH & stats.st_mode)?(permissions[9]='x'):(permissions[9]='-');
    permissions[10]='\0';
    struct passwd *user  = getpwuid(stats.st_uid);
    struct group *grp  = getgrgid(stats.st_gid);
    char * modified = ctime(&stats.st_mtime);
    char actual_modified[1000] = "";int it=0;
    for(int i=4;i<strlen(modified)-9;i++){
        actual_modified[it++]=modified[i];
    }
    actual_modified[strlen(actual_modified)]='\0';
    printf("%s %lu %s %s %ld %s %s\n",permissions,stats.st_nlink,user->pw_name,grp->gr_name,stats.st_size,actual_modified,present);
}
void ls(char ** split,char * pwd){
    int count=0;
    for(int i=0;i<10;i++){
        if(strlen(split[i])!=0){
            count++;
        }
    }
    if(strcmp(split[count],"\n")==0){
        count--;
        int t = strlen(split[count]);
        split[count][t]='\n';
        split[count][t+1]='\0';
    }
    int parameters[3]={0,0,0},t=0;
    for(int i=1;i<=count;i++){
        if(split[i][0]=='-'){
            parameters[i-1]=1;
            t++;
        }
    }
    char * working;
    if(!count | count == t){
        char cwd[50];
        if(getcwd(cwd,50)!=NULL){
            working="./";
        }
        else{
            perror("");
        }
    }
    else if(!t){
        working = acutalDEST(split[1],pwd);
    }
    else{
        int direc = 0;
        for(int i=2;i>=0;i--){
            if(!parameters[i]){
                direc=i;
            }
        }
        working=acutalDEST(split[direc+1],pwd);
    }
    int length = strlen(working);
    struct dirent * direc;DIR* p;
    p = opendir(working);
    if(!t){
        if(!p){
            perror("");
        }
        else{
            while(direc = readdir(p)){
                if(direc->d_name[0]!='.')
                    printf("%s ",direc->d_name);
            }
            printf("\n");
        }
    }
    else{
        int a=0,l=0;
        for(int i=0;i<3;i++){
            if(parameters[i]){
                if(strcmp(split[i+1],"-a")==0 | strcmp(split[i+1],"-a\n")==0){
                    a=1;
                }
                else if(strcmp(split[i+1],"-l")==0 | strcmp(split[i+1],"-l\n")==0){
                    l=1;
                }
                else if(strcmp(split[i+1],"-al\n")==0 | strcmp(split[i+1],"-al")==0 | strcmp(split[i+1],"-la")==0 | strcmp(split[i+1],"-la\n")==0){
                    a=1;l=1;
                }
                else{
                    printf("INVALID ARGUMENT\n");
                    return;
                }
            }
        }
        if(a && !l){
            if(!p){
                perror("");
            }
            else{
                while(direc = readdir(p)){
                    printf("%s ",direc->d_name);
                }
                printf("\n");
            }
        }
        else if(!a && l){
            if(!p){
                perror("");
            }
            else{
                while(direc = readdir(p)){
                    if(direc->d_name[0]!='.')
                        information(direc->d_name);
                }
            }
        }
        else{
            if(!p){
                perror("");
            }
            else{
                while(direc = readdir(p)){
                    information(direc->d_name);
                }
            }
        }
    }
}