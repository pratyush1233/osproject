#include <iostream>
#include <queue>
using namespace std;

struct Process {
    int pid;  
    int priority;  
    int burst_time;  
    int remaining_time;  
};


struct Compare {
    bool operator()(const Process& p1, const Process& p2) {
        return p1.priority > p2.priority;  
    }
};


int main() {
    
    priority_queue<Process, vector<Process>, Compare> q1;
    
    queue<Process> q2;

    q1.push({1, 0, 8, 8});
    q1.push({2, 1, 4, 4});
    q1.push({3, 2, 9, 9});
    q1.push({4, 1, 5, 5});

   
    int time = 0;

   
    Process current_process = {-1, -1, -1, -1};

    
    while (!q1.empty() || !q2.empty()) {
        
        if (!q1.empty() && (current_process.pid == -1 || q1.top().priority < current_process.priority)) 
            
             
