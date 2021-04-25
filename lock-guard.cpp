/*
    Lock Guard - A simple wrapper to help scope mutex
        - A thread will acquire the lock the moment the lock_guard is created

        - Once the thread leaves the scope (ex. function), the mutex
          is unlocked

        - The lock_guard cannot be explicitly unlocked
*/

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex m;
int buffer = 0, buffer_lock_guard = 0;

void task(const char *threadName, int loopFor)
{
    m.lock();
    for (int i = 0; i < loopFor; i++)
    {
        buffer++;
        cout << threadName << ": " << buffer << endl;
    }
    m.unlock();
}

void task_lock_guard(const char *threadName, int loopFor)
{
    std::lock_guard<mutex> lock(m);
    for (int i = 0; i < loopFor; i++)
    {
        buffer_lock_guard++;
        cout << threadName << ": " << buffer_lock_guard << endl;
    }
}

int main()
{
    cout << "----- No Lock Guard / Manual Lock/Unlock -----" << endl;
    thread t1(task, "Thread 1", 10);
    thread t2(task, "Thread 2", 10);
    t1.join();
    t2.join();

    cout << endl
         << "----- With Lock Guard -----" << endl;
    thread t3(task_lock_guard, "Thread 1", 10);
    thread t4(task_lock_guard, "Thread 2", 10);
    t3.join();
    t4.join();

    return 0;
}