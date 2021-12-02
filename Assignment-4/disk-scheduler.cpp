#include <iostream>
#include <queue>
#include <set>
#include <vector>
#include <fstream>
#include <algorithm>
#include <list>
#include <string>

using namespace std;
template<class Container> int traverseHead(Container& container, int& head);
int main(int argc, char const *argv[])
{  
    if (argc != 3) {
        cout << "Invalid arguments" << endl;
        return 1;
    }
    int initialPos = stoi(argv[1]);
    vector<int> requests;
    ifstream input("input.txt");
    //Read data
    int value;
    while (input >> value){
        requests.push_back(value);
    }
    value = initialPos;
    int seekTotal = 0;
    queue<int> FCFS(std::deque<int>(requests.begin(), requests.end()));
    while (FCFS.size() > 0){
        int distance = abs(FCFS.front() - value);
        value = FCFS.front();
        seekTotal += distance;
        FCFS.pop();
    }
    cout << seekTotal << endl;
    value = initialPos;
    seekTotal = 0;
    deque<int> SSFT(requests.begin(), requests.end());
    while (!SSFT.empty()){
        sort(SSFT.begin(), SSFT.end(), [value](int lhs, int rhs){return abs(lhs - value) < abs(rhs - value);});
        int distance = abs(SSFT.front() - value);
        value = SSFT.front();
        seekTotal += distance;
        SSFT.pop_front();
    }
    cout << seekTotal << endl;
    //Scan
    vector<int> up;
    vector<int> down;
    for (auto& x: requests){
        if (x < initialPos)
            down.push_back(x);
        if (x >= initialPos)
            up.push_back(x);
    }
    sort(up.begin(), up.end());
    sort(down.begin(), down.begin());
    bool direction = argv[2] == "upwards";
    value = initialPos;
    seekTotal = traverseHead(direction ? up: down, value);
    seekTotal += traverseHead(direction ? down: up, value);
    cout << seekTotal << endl;
    return 0;
}
template<class Container> int traverseHead(Container& container, int& head){
    int seekTime = 0;
    for(auto& x: container){
        seekTime += abs(x - head);
        head = x;
    }
    return seekTime;
}