
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int priority;
};

struct ComparePriority {
    bool operator()(const Process& p1, const Process& p2) {
        return p1.priority < p2.priority;
    }
};

void roundRobinWithPriority(vector<Process>& processes, int quantum) {
    priority_queue<Process, vector<Process>, ComparePriority> priorityQueue;
    queue<Process> readyQueue;
    int currentTime = 0;
    int totalProcesses = processes.size();
    int completedProcesses = 0;

    while (completedProcesses < totalProcesses) {
        // Adding arriving processes to the priority queue
        for (int i = 0; i < totalProcesses; ++i) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                priorityQueue.push(processes[i]);
            }
        }

        // Adding processes from the priority queue to the ready queue
        while (!priorityQueue.empty()) {
            readyQueue.push(priorityQueue.top());
            priorityQueue.pop();
        }

        if (!readyQueue.empty()) {
            Process currentProcess = readyQueue.front();
            readyQueue.pop();

            int executeTime = min(quantum, currentProcess.remainingTime);
            currentTime += executeTime;
            currentProcess.remainingTime -= executeTime;

            cout << "Process " << currentProcess.id << " executed for " << executeTime << " units at time " << currentTime << endl;

            if (currentProcess.remainingTime <= 0) {
                completedProcesses++;
                cout << "Process " << currentProcess.id << " completed at time " << currentTime << endl;
            } else {
                readyQueue.push(currentProcess);
            }
        } else {
            currentTime++;
        }
    }
}

int main() {
    vector<Process> processes = {
        {1, 0, 5, 5, 2},
        {2, 1, 3, 3, 1},
        {3, 2, 8, 8, 3},
        {4, 3, 6, 6, 2}
    };

    int quantum = 2;

    roundRobinWithPriority(processes, quantum);

    return 0;
}













