#include <iostream>
#include <fstream>
#include <queue>
#include <deque>
#include <algorithm>
#include <stdio.h>
using namespace std;
int main(int argc, char const *argv[])
{
    ifstream input("input.csv");
    string cell;
    queue<int> requests;
    deque<int> requestsRound2;
    const int frames = 10;
    while (getline(input, cell, ','))
    {
        requests.push(stoi(cell));
    }
    //FIFO
    deque<int> loadedPages;
    int faultCount = 0;
    while (requests.size() > 0)
    {
        int page = requests.front(); requests.pop();
        requestsRound2.push_back(page);
        printf("\nPage: %d\n", page);
        for(auto x: loadedPages){
            printf("%d, ", x);
        }
        printf("\n");
        if (find(loadedPages.begin(), loadedPages.end(), page) != loadedPages.end())
            continue;
        if (loadedPages.size() == frames){
            loadedPages.pop_front();
        }
        cout << "page fault triggered\n";
        faultCount++;
        loadedPages.push_back(page);
    }
    printf("Page fault count: %d\n%s", faultCount, string('-', 10).c_str());
    //Optimal page replacement
    loadedPages.clear();
    faultCount = 0;
    for(int i = 0; i < requestsRound2.size(); i++){
        int page = requestsRound2[i];
        printf("\nPage: %d\n", page);
        for(auto x: loadedPages){
            printf("%d, ", x);
        }
        printf("\n");
        if (find(loadedPages.begin(), loadedPages.end(), page) != loadedPages.end())
            continue;
        if (loadedPages.size() == frames){
            int index = 0; int lastPos = INT16_MIN;
            for (int j = 0; j < loadedPages.size(); j++){
                int pos = distance(find(requestsRound2.begin() + i, requestsRound2.end(), loadedPages[j]), requestsRound2.end());
                if (pos > lastPos){
                    lastPos = pos;
                    index = i;
                }
            }
            loadedPages.at(index) = page;
        }else{
            loadedPages.push_back(page);
        }
        cout << "page fault triggered\n";
        faultCount++;
    }
    printf("Page fault count: %d\n%s", faultCount, string('-', 10).c_str());
    return 0;
}