// Bankers algo
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to check if a state is safe
bool isSafe(const vector<vector<int>>& allocation,
            const vector<vector<int>>& max,
            const vector<int>& available,
            const vector<bool>& finished) {
    int numProcesses = allocation.size();
    int numResources = available.size();

    vector<int> work = available;
    vector<bool> finish = finished;

    // Find an unfinished process that can be satisfied
    int process;
    bool found = false;
    for (int i = 0; i < numProcesses; ++i) {
        if (!finish[i]) {
            bool canFinish = true;
            for (int j = 0; j < numResources; ++j) {
                if (max[i][j] - allocation[i][j] > work[j]) {
                    canFinish = false;
                    break;
                }
            }
            if (canFinish) {
                process = i;
                found = true;
                break;
            }
        }
    }

    if (!found)
        return false;

    // Pretend to allocate resources to process and check if it completes
    for (int j = 0; j < numResources; ++j)
        work[j] += allocation[process][j];
    finish[process] = true;

    return isSafe(allocation, max, work, finish);
}

// Banker's Algorithm
bool bankersAlgorithm(const vector<vector<int>>& allocation,
                      const vector<vector<int>>& max,
                      const vector<int>& available) {
    int numProcesses = allocation.size();
    int numResources = available.size();

    // Initialize a vector to track finished processes
    vector<bool> finished(numProcesses, false);

    // Check if the system is in a safe state
    return isSafe(allocation, max, available, finished);
}

int main() {
    // Example allocation matrix
    vector<vector<int>> allocation = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    // Example max matrix
    vector<vector<int>> max = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    // Example available resources
    vector<int> available = {3, 3, 2};

    // Check if the system is in a safe state
    if (bankersAlgorithm(allocation, max, available))
        cout << "System is in a safe state." << endl;
    else
        cout << "System is in an unsafe state." << endl;

    return 0;
}
