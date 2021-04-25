/*
    Recursive Mutex
        - recursive_mutex allows the same thread to lock one mutex 
          multiple times (ex. in a recursive call)

        - logic must be written to unlock the mutex the same amount
          of times as it was locked
*/

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

recursive_mutex m1;
int buffer = 0;

void recursion(char c, int loopFor)
{
    if (loopFor < 1)
        return;

    m1.lock();
    cout << "Thread " << c << ": " << buffer++ << endl;
    recursion(c, --loopFor);
    m1.unlock();
}

int main()
{
    // One thread will wait until the other counts to 10
    thread t1(recursion, '0', 10);
    thread t2(recursion, '1', 10);
    t1.join();
    t2.join();
    return 0;
}