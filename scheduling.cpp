#include <iostream>
#include <queue>
using namespace std;

// Process struct representing a process with its details
struct Process
{
    int pid;            // Process ID
    int priority;       // Priority level (0 is highest)
    int burst_time;     // Time required for execution
    int remaining_time; // Time remaining for execution
    int quantum;        // Time quantum for round robin scheduling

    Process(int pid, int priority, int burst_time, int quantum)
    {
        this->pid = pid;
        this->priority = priority;
        this->burst_time = burst_time;
        this->remaining_time = burst_time;
        this->quantum = quantum;
    }
};

// Compare function for priority queue (lower priority value has higher priority)
struct ComparePriority
{
    bool operator()(const Process &p1, const Process &p2)
    {
        return p1.priority > p2.priority;
    }
};

// Compare function for round robin queue (higher remaining time value has lower priority)
struct CompareRR
{
    bool operator()(const Process &p1, const Process &p2)
    {
        return p1.remaining_time < p2.remaining_time;
    }
};

int main()
{
    int num_processes, quantum;
    cout << "Enter the number of processes: ";
    cin >> num_processes;
    cout << "Enter the time quantum for round robin scheduling: ";
    cin >> quantum;

    // Priority queue for level 1 processes
    priority_queue<Process, vector<Process>, ComparePriority> q1;

    // Round robin queue for level 2 processes
    priority_queue<Process, vector<Process>, CompareRR> q2;

    // Input the processes
    for (int i = 0; i < num_processes; i++)
    {
        int pid, priority, burst_time;
        cout << "Enter details for process " << i + 1 << endl;
        cout << "Process ID: ";
        cin >> pid;
        cout << "Priority: ";
        cin >> priority;
        cout << "Burst Time: ";
        cin >> burst_time;
        q1.push(Process(pid, priority, burst_time, quantum));
    }

    // Simulation loop
    int current_time = 0;
    while (!q1.empty() || !q2.empty())
    {
        // Check if there are any processes in level 1 queue
        if (!q1.empty())
        {
            // Execute the highest priority process in level 1 queue
            Process p = q1.top();
            q1.pop();
            cout << "Executing process " << p.pid << " from queue 1 at time " << current_time << endl;

            // Execute the process for a multiple of 2 time units
            int execution_time = min(p.remaining_time, 2);
            current_time += execution_time;
            p.remaining_time -= execution_time;

            // Check if the process has completed or needs to be moved to level 2 queue
            if (p.remaining_time > 0)
            {
                // Update the priority and quantum of the process and move it to level 2 queue
                p.priority = 1;
                p.quantum = quantum;
                q2.push(p);
            }
            else
            {
                // The process has completed
                cout << "Process " << p.pid << " completed at time " << current_time << endl;
            }
        }
        else if (!q2.empty())
        {
            // Execute the highest priority process in level 2 queue
            Process p = q2.top();
            q2.pop();
            cout << "Executing process " << p.pid << " from queue 2 at time " << current_time << endl;

            // Execute the process for a time quantum
            int execution_time = min(p.remaining_time, p.quantum);
            current_time += execution_time;
            p.remaining_time -= execution_time;

            // Check if the process has completed or needs to be moved back to level 1 queue
            if (p.remaining_time > 0)
            {
                // Update the quantum of the process and move it back to level 1 queue
                p.quantum *= 2;
                q1.push(p);
            }
            else
            {
                // The process has completed
                cout << "Process " << p.pid << " completed at time " << current_time << endl;
            }
        }
    }

    return 0;
}
