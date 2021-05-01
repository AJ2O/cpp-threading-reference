/*
    Lock ( std::lock() )
        - Used to lock multiple mutexes at the same time
        - NOT a wrapper by default, have to manually unlock
            - Can wrap mutexes with lock_guard, unique_lock, etc. to
              automatically unlock
        
    Syntax - std::lock(m1, m2, m3, ...);
        - mx = mutex x

    Info
        - All arguments are locked via a sequence of calls to lock(), 
            try_lock(), or unlock() on each argument
        - Locking order is not defined
        - It is a blocking call
            - ex. will wait until all its assigned mutexes are unlocked

    Example Situations
        - 1. No Deadlock
            - Thread 1, lock(m1, m2);
            - Thread 2, lock(m1, m2);

        - 2. No Deadlock
            - Thread 1, lock(m1, m2);
            - Thread 2, lock(m2, m1);

        - 3. No Deadlock
            - Thread 1, lock(m1, m2, m3, m4);
            - Thread 2, lock(m3, m4);
                        lock(m1, m2);

        - 4. Deadlock
            - Thread 1, lock(m1, m2);
                        lock(m3, m4);

            - Thread 2, lock(m3, m4);
                        lock(m1, m2);
*/

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex m1, m2, m3, m4;

void ex_1a()
{
    while (1)
    {
        std::lock(m1, m2);
        std::cout << "task a\n";
        m1.unlock();
        m2.unlock();
    }
}
void ex_1b()
{
    while (1)
    {
        std::lock(m1, m2);
        std::cout << "task b\n";
        m1.unlock();
        m2.unlock();
    }
}

void ex_2a()
{
    while (1)
    {
        std::lock(m1, m2);
        std::cout << "task a\n";
        m1.unlock();
        m2.unlock();
    }
}
void ex_2b()
{
    while (1)
    {
        std::lock(m2, m1);
        std::cout << "task b\n";
        m1.unlock();
        m2.unlock();
    }
}

void ex_3a()
{
    while (1)
    {
        std::lock(m1, m2, m3, m4);
        std::cout << "task a\n";
        m1.unlock();
        m2.unlock();
    }
}
void ex_3b()
{
    while (1)
    {
        std::lock(m3, m4);
        std::lock(m1, m2);
        std::cout << "task b\n";
        m1.unlock();
        m2.unlock();
    }
}

void ex_4a()
{
    while (1)
    {
        std::lock(m1, m2);
        std::lock(m3, m4);
        std::cout << "task a\n";
        m1.unlock();
        m2.unlock();
    }
}
void ex_4b()
{
    while (1)
    {
        std::lock(m3, m4);
        std::lock(m1, m2);
        std::cout << "task b\n";
        m1.unlock();
        m2.unlock();
    }
}

int main()
{
    thread t1(ex_4a);
    thread t2(ex_4b);
    t1.join();
    t2.join();

    return 0;
}
