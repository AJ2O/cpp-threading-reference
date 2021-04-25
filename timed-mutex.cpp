/*
    Timed Mutex
        - std::timed_mutex blocks other threads until the specified timeout
        
        - try_lock_for() attempts to lock for a specified length of time
        - try_lock_until() attempts to lock until a specified time

        - When the second thread reaches the lock...
            - If the locking thread finishes before the timeout, the functions return True
            - False otherwise

*/
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
using namespace std;

int x = 0, y = 0;
timed_mutex m;

void AddToX(int i)
{
    // Try the lock for 1 second
    if (m.try_lock_for(chrono::seconds(1)))
    {
        // The first thread will lock the second thread out
        ++x;
        this_thread::sleep_for(chrono::seconds(2));
        cout << "Thread " << i << " could lock" << endl;
        m.unlock();
    }
    else
    {
        // Since the second thread is locked out, it will reach here
        cout << "Thread " << i << " could not lock" << endl;
    }
}

void AddToYUntil(int i)
{
    // Try the lock until a specified date (1 second from now)
    auto now = chrono::steady_clock::now();
    if (m.try_lock_until(now + chrono::seconds(1)))
    {
        // The first thread will lock the second thread out
        ++y;
        this_thread::sleep_for(chrono::seconds(2));
        cout << "Thread " << i << " could lock" << endl;
        m.unlock();
    }
    else
    {
        // Since the second thread is locked out, it will reach here
        cout << "Thread " << i << " could not lock" << endl;
    }
}

int main()
{
    thread t1(AddToX, 1);
    thread t2(AddToX, 2);
    t1.join();
    t2.join();
    cout << x << endl;

    thread t3(AddToYUntil, 3);
    thread t4(AddToYUntil, 4);
    t3.join();
    t4.join();
    cout << y << endl;

    return 0;
}