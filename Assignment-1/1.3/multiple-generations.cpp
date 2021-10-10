#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
int main(int argc, char const *argv[])
{
    pid_t pid = fork(); //Create the C process
    if (pid == 0){
        printf("%d I am the parent process\n", getpid());
        pid = fork(); //Create the GC process
        if (pid == 0){
            printf("%d I am the grandchild process\n", getpid());
        }
    }else{
        printf("%d I am the grandparent process\n", getpid());
    }
    //Wait for all children to die
    //I wanted to exclude this statement because parents and grandparents *usually* die before their children
    //but that made my terminal look wierd because of the grandparent terminating before the GC died.
    wait(NULL); 
    return 0;
}
