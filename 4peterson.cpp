#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

#define THREADS 2

atomic<int> turn;
atomic<bool> flag[THREADS];

void enter_critical_section(int thread_id) {
    int other = 1 - thread_id;
    flag[thread_id] = true;
    turn = other;

    // Wait until the other thread isn't in its critical section
    while (flag[other] && turn == other)
        std::this_thread::yield();
}

void exit_critical_section(int thread_id) {
    flag[thread_id] = false;
}

void critical_section(int thread_id) {
    enter_critical_section(thread_id);
    // Critical Section
    cout << "Thread " << thread_id << " is in critical section." << endl;
    exit_critical_section(thread_id);
}

void thread_function(int thread_id) {
    // Do some non-critical work
    cout << "Thread " << thread_id << " is doing some non-critical work." << endl;
    // Enter the critical section
    critical_section(thread_id);
    // Do some more non-critical work
    cout << "Thread " << thread_id << " is doing some more non-critical work." << endl;
}

int main() {
    turn = 0;
    flag[0] = false;
    flag[1] = false;

    thread t1(thread_function, 0);
    thread t2(thread_function, 1);

    t1.join();
    t2.join();

    return 0;
}
