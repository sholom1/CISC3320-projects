#include <iostream>
#include <boost/dynamic_bitset.hpp>
#include <mutex>
#include <thread>
using namespace std;
class PidManager {
    private:
        int minSize;
        int maxSize;
        boost::dynamic_bitset<uint8_t> pids;
    public:
        PidManager(int min, int max): minSize(min), maxSize(max), pids(max-min, 0){
            pids.set();
        };
        PidManager(const PidManager& other): PidManager(other.minSize, other.maxSize){};
        int allocate_pid(){
            unsigned long id;
            if (pids.any()){
                id = pids.find_first();
                pids.set(id, false);
                id += this->minSize;
            }else{
                id = -1;
            }
            return id;
        };
        void release_pid(int pid){
            pids.set(pid, true);
        }

};
void job(PidManager& pids, mutex& mu, double sleepTime){
    mu.lock();
    auto pid = pids.allocate_pid();
    cout << "PID: " << pid << " successfully allocated on thread-" << this_thread::get_id() << endl;
    cout << "PID: " << pid << " is going to sleep" << endl;
    mu.unlock();
    sleep(sleepTime);
    mu.lock();
    cout << "PID: " << pid << " is being released" << endl;
    pids.release_pid(pid);
    mu.unlock();
}
int main(int argc, char const *argv[])
{
    constexpr int MIN_SIZE = 300;
    constexpr int MAX_SIZE = 5000;
    PidManager pids = PidManager(MIN_SIZE, MAX_SIZE);
    thread threads[50];
    mutex mu;
    srand(time(NULL));
    for (int i = 0; i < 50; i++){
        threads[i] = thread {job, ref(pids), ref(mu), rand() % 3 + .1};
    }
    for (auto& t: threads) t.join();
    return 0;
}
