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
    const int diskMin = 0;
    const int diskMax = 4999;
    int head;
    int seekTotal = 0;
    //Read data from file
    while (input >> head){
        requests.push_back(head);
    }
    //Move the head to the initial position
    head = initialPos;
    //FCFS: First Come First Serve
    //We can just iterate through the request vector without any preprocessing
    cout << "FCFS: First Come First Serve" << endl;
    seekTotal = traverseHead(requests, head);
    cout << "Total seek operations: " << seekTotal << endl << endl;
    //Reset head and seekTotal
    head = initialPos;
    seekTotal = 0;
    //SSTF: Shortest Seek Time First
    cout << "SSTF: Shortest Seek Time First" << endl;
    //First copy all the values from requests into an deque
    deque<int> SSFT(requests.begin(), requests.end());
    //Iterate through all requests
    while (!SSFT.empty()){
        //Each iteration sort to find the request with the shortest travel time from the head.
        sort(SSFT.begin(), SSFT.end(), [head](int lhs, int rhs){return abs(lhs - head) < abs(rhs - head);});
        int distance = abs(SSFT.front() - head);
        head = SSFT.front();
        cout << "Traversing to: " << head << endl;
        seekTotal += distance;
        SSFT.pop_front();
    }
    cout << "Total seek operations: " << seekTotal << endl << endl;
    //Scan
    cout << "Scan (Elevator) Algorithm" << endl;
    //Create two vectors representing the requests above and below the head
    vector<int> up;
    vector<int> down;
    //Iterate through requests inserting the elements into the correct buckets
    for (auto& x: requests){
        if (x < initialPos)
            down.push_back(x);
        if (x >= initialPos)
            up.push_back(x);
    }
    //Check if we even need to traverse to the other end of the disk before inserting the bounds
    if (up.size() > 0) up.push_back(diskMax);
    if (down.size() > 0) down.push_back(diskMin);
    //sort the vectors
    sort(up.begin(), up.end());
    //the down one should be sort in descending order
    sort(down.begin(), down.end(), greater<int>());
    //Determine desired direction flag
    bool direction = argv[2] == "upwards";
    head = initialPos;
    //traverse each of the buckets depending on the direction
    seekTotal = traverseHead(direction ? up: down, head);
    seekTotal += traverseHead(direction ? down: up, head);
    cout << "Total seek operations: " << seekTotal << endl << endl;
    return 0;
}
template<class Container> int traverseHead(Container& container, int& head){
    int seekTime = 0;
    for(auto& x: container){
        cout << "Traversing to: " << x << endl;
        seekTime += abs(x - head);
        head = x;
    }
    return seekTime;
}