#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/utsname.h>
#include<unistd.h>
void pwd(void){
    char correctPWD[1000];
    getcwd(correctPWD,1000);
    printf("%s\n",correctPWD);
}