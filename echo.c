#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/utsname.h>
#include<unistd.h>
void echo(char ** split){
    int count=0;
    for(int i=1;i<10;i++){
        int t= strlen(split[i]);
        if(t!=0){
            count++;
        }
    }
    if(strcmp(split[count],"\n")==0){
        count--;
        int t = strlen(split[count]);
        split[count][t]='\n';
        split[count][t+1]='\0';
    }
    for(int i=1;i<=count;i++){
        if(i!=count)
            printf("%s ",split[i]);
        else
            printf("%s\n",split[i]);
    }
}  