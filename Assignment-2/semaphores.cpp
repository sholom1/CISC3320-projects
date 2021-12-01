#include <iostream>
#include <string>
#include <queue>
#include <unordered_set>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>       
#include <unistd.h>
#include <time.h>
#include <mutex>

using namespace std;
#pragma region declarations
struct ResourceRequest{
    int pid;
    void (*request)();
};
class Semaphore {
    private:
        string name;
        int avaliableResources;
        queue<int> requestQueue;
        unordered_set<int> activeRequests;
        mutex &resource_mutex;
    public:
        Semaphore(const char * name, int size, mutex &mu) : name(name), avaliableResources(size), resource_mutex(mu){
            this->requestQueue = queue<int>();
            this->activeRequests = unordered_set<int>(size);
        };
        bool RequestResource(int pid);
        void ReleaseResource(int pid);
};
void randSleep();
#pragma endregion
int main(int argc, char const *argv[])
{
    //Create locks for each resource
    mutex mu_pr, mu_pl, mu_ps;
    //Create semaphores
    Semaphore resources[] = {Semaphore("Printer", 5, mu_pr), Semaphore("Plotters", 6, mu_pl), Semaphore("Scanners", 4, mu_ps)};
    //Initilize random
    srand(time(0));
    for (int i = 0; i < 100; i++){
        int val = rand() % 3;
        int pid = fork();
        if (pid == 0){
            bool fulfilled = resources[val].RequestResource(getpid());
            if (!fulfilled){
                pause();
            }
            randSleep();
            resources[val].ReleaseResource(getpid());
            exit(0);
        }
    }
    for (int i = 0; i < 100; i++) wait(NULL);
    return 0;
}
bool Semaphore::RequestResource(int pid){
    //Wait until lock is avaliable
    while(!this->resource_mutex.try_lock()){cout<<"Resource locked"<<endl;};
    bool avaliable = this->avaliableResources > 0;
    cout << "The process with pid: " + to_string(pid) + " requests a " + this->name + " resource" << endl;
    cout << "The " + this->name + " semaphore has " + to_string(this->avaliableResources) + " resources avaliable" << endl;
    //sleep(1);
    if (avaliable){
        cout << "Resource is avaliable" << endl;
        this->avaliableResources--;
        activeRequests.insert(pid);
    }else{
        cout << "Request failed, request has been placed in queue" << endl;
        this->requestQueue.push(pid);
    }
    this->resource_mutex.unlock();
    return avaliable;
}
void Semaphore::ReleaseResource(int pid){
    cout << "The process with pid: " + to_string(pid) + " Has completed it's request" << endl;
    while(!this->resource_mutex.try_lock()){cout<<"Resource locked"<<endl;};
    if (this->activeRequests.erase(pid)){
        if (requestQueue.size() > 0){
            auto next = requestQueue.front();
            requestQueue.pop();
            kill(next, SIGCONT);
        }else{
            this->avaliableResources++;
        }
    }
    this->resource_mutex.unlock();
}
void randSleep(){
    //sleep(rand() % 100 + 1);
    sleep(rand() % 4 + 1);
}