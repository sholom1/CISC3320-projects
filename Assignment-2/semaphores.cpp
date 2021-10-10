#include <iostream>
#include <string>
#include <queue>
#include <unordered_set>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>       
#include <unistd.h>
#include <time.h>

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
        queue<ResourceRequest> requestQueue;
        unordered_set<int> activeRequests; 
    public:
        Semaphore(const char * name, int size);
        bool RequestResource(ResourceRequest req);
        void ReleaseResource(int pid);
};
void randSleep();
#pragma endregion
int main(int argc, char const *argv[])
{
    srand(time(NULL));
    Semaphore resources[] = {Semaphore("Printer", 5), Semaphore("Plotters", 6), Semaphore("Scanners", 4)};
    for (int i = 0; i < 100; i++){
        int pid = fork();
        if (pid == 0){
            cout << rand() % 3 << endl;
            Semaphore selectedResource = resources[rand() % 3];
            bool fulfilled = selectedResource.RequestResource({getpid(), randSleep});
            if (!fulfilled){
                pause();
            }
            exit(0);
        }
    }
    wait(NULL);
    return 0;
}
Semaphore::Semaphore(const char * name, int size){
    this->name = string(name);
    this->requestQueue = queue<ResourceRequest>();
    this->activeRequests = unordered_set<int>(size);
    this->avaliableResources = size;
}
bool Semaphore::RequestResource(ResourceRequest req){
    bool avaliable = this->avaliableResources > 0;
    cout << "The process with pid: " + to_string(req.pid) + " requests a " + this->name + " resource" << endl;
    cout << "The " + this->name + " semaphore has " + to_string(this->avaliableResources) + " resources avaliable" << endl;
    if (avaliable){
        cout << "Request success" << endl;
        this->avaliableResources--;
        activeRequests.insert(req.pid);
        req.request();
        this->ReleaseResource(req.pid);
    }else{
        cout << "Request failed, request has been placed in queue" << endl;
        this->requestQueue.push(req);
    }
    return avaliable;
}
void Semaphore::ReleaseResource(int pid){
    if (this->activeRequests.erase(pid)){
        this->avaliableResources++;
        if (requestQueue.size() > 0){
            auto next = requestQueue.front();
            requestQueue.pop();
            RequestResource(next);
        }
    }
}
void randSleep(){
    sleep(rand() % 4 + 1);
}