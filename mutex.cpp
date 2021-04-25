/*
    Mutex : Mutual Exclusion (<mutex>)
        - Mutex is used to avoid race conditions between different
          threads that attempt to access the the same variable

        - The Mutex object should be placed around the section of
          code that should be locked to a single thread only
*/

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int x = 0, endResult = 0;
mutex m, mt;

void AddToX()
{
    // one thread will lock the mutex first
    // the second thread will be blocked until the mutex becomes free
    m.lock();
    for (int i = 0; i < 100000; i++)
    {
        ++x;
    }
    // once unlocked, any pending threads will continue their execution
    m.unlock();
}

// try_lock attempts to lock the mutex, but unlike lock, the thread will
// not stop if it fails to lock
void AddToXTryLock()
{
    for (int i = 0; i < 100000; i++)
    {
        if (mt.try_lock())
        {
            ++endResult;
            mt.unlock();
        }
    }
}

int main()
{
    // Regular lock
    // both threads start in parallel
    thread t1(AddToX);
    thread t2(AddToX);
    t1.join();
    t2.join();
    cout << "100000 + 100000 --- lock() has the result: " << x << endl;

    // Try Lock
    // Running this program multiple times will yield different answers
    // Under normal lock(), the result will always be 200,000
    endResult = 0;
    thread t3(AddToXTryLock);
    thread t4(AddToXTryLock);
    t3.join();
    t4.join();
    cout << "100000 + 100000 --- try_lock() has the result: " << endResult << endl;

    return 0;
}