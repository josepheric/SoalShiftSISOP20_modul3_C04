#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
int main(){
    pid_t pid;
    int status;
    int p[2];
    pipe(p);
    pid=fork();
    if(pid<0){
        exit(EXIT_FAILURE);
    }
    else if(pid==0){
        dup2(p[1],STDOUT_FILENO);//child
        close(p[0]);
        close(p[1]);
        char *argv[]={"ls",NULL};
        execv("/bin/ls",argv);
    }
    else{ //parent
        while(wait(&status)>0);
        dup2(p[0],STDIN_FILENO);
        close(p[1]);
        close(p[0]);
        char *argv1[]={"wc","-l",NULL};
        execv("/usr/bin/wc",argv1);
    }
    return 0;
}
