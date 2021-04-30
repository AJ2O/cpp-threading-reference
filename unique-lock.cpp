/*
    Unique Lock ( std::unique_lock<mutex> )
        - The unique_lock class is a mutex ownership wrapper
        - It allows for:
            - a. Can have different locking strategies:
                - defer_lock    = own the mutex, but do not lock the mutex immediately
                - try_to_lock   = try to own mutex without blocking
                - adopt_lock    = assume the calling thread already has ownership of the mutex
            
            - b. time-constrained (try_lock)

            - c. recursive locking

            - d. transfer lock ownership

            - e. condition variables (synchronizing threads on conditions)
*/

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex m;
int buffer = 0;

// No strategy: like lock_guard.
void noStrategy(const char *threadID, int loopFor)
{
    unique_lock<mutex> lock(m);
    for (int i = 0; i < loopFor; i++)
    {
        buffer++;
        cout << threadID << ": " << buffer << endl;
    }
}

void deferLock(const char *threadID, int loopFor)
{
    unique_lock<mutex> lock(m, std::defer_lock);

    // random code here, lock is deferred

    m.lock();
    for (int i = 0; i < loopFor; i++)
    {
        buffer++;
        cout << threadID << ": " << buffer << endl;
    }
}

int main()
{
    thread t1(noStrategy, "Thread 0", 10);
    thread t2(noStrategy, "Thread 1", 10);
    t1.join();
    t2.join();

    thread t3(deferLock, "Thread 2", 10);
    thread t4(deferLock, "Thread 3", 10);
    t3.join();
    t4.join();

    return 0;
}
