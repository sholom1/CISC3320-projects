#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <list>
using namespace std;
int main(int argc, char const *argv[])
{
    list<pid_t> children;
    for (int i = 0; i < 4; i++){
        pid_t pid = fork();
        if (pid == 0){
            //I am child it is my bedtime. Must sleep.
            sleep(4);
            return 0; //return early to stop the child contiuning its own iteration of the for loop
        }else{
            children.push_back(pid);
            cout << "Children: ";
            //Print list of children
            for (auto const &i : children){
                cout << i << " ";
            }
            cout << endl;
        }
    }
    return 0;
}
