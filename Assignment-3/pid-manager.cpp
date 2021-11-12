#include <iostream>
#include <boost/dynamic_bitset.hpp>
using namespace std;
class PidManager {
    private:
        int minSize;
        int maxSize;
        boost::dynamic_bitset<uint8_t> pids;
    public:
        PidManager(int min, int max){
            this->minSize = min;
            this->maxSize = max;
            pids = boost::dynamic_bitset<uint8_t>(max-min, 0);
        };
        size_t allocate_pid(){
            auto id = pids.find_first();
            cout << id << endl;
            pids.set(id, true);
            return id;
        }
        size_t size(){return pids.size();};

};
int main(int argc, char const *argv[])
{
    constexpr int MIN_SIZE = 300;
    constexpr int MAX_SIZE = 5000;
    PidManager pids = PidManager(MIN_SIZE,MAX_SIZE);
    cout << "Size: " << pids.size() << ", First position: " << pids.allocate_pid() << endl;
    return 0;
}
