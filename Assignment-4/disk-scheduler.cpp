#include <iostream>
#include <queue>
#include <set>
#include <vector>
#include <fstream>
#include <algorithm>
#include <list>

using namespace std;
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
    //Scan
    sort(requests.begin(), requests.end());
    for (auto& x: requests) cout << x << " ";
    cout << endl;
    auto mid = 
    cout << seekTotal << endl;
    return 0;
}
