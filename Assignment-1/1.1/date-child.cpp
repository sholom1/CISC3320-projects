#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctime>
#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
    if (fork() == 0){
        //get the time and convert it to localtime
        time_t rawTime;
        time(&rawTime);
        tm * timeNow = localtime(&rawTime);
        //Weekday array for day lookup
        const char * weekday[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
        printf("I'm a child process\n");
        printf("Today is %s.\n", weekday[timeNow->tm_wday]);
        printf("My pid is %d \n", getpid());
        printf("My parents pid is %d \n", getppid());
    }
    else{
        //Wait for child to finish.
        wait(NULL);
    }
    return 0;
}
