/*
    Condition Variables
        - Used to synchronize threads by:
            - Waiting threads on certain conditions
            - Notifying waiting threads to continue

        - Notification functionality:
            - notify_one();
                - If some threads are waiting on certain conditions, only one of them is notified
            - notify_all();
                - If some threads are waiting on certain conditions, all threads are notified
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

mutex m;
condition_variable cv;
long balance = 0;

void depositMoney(int money)
{
    // locks the mutex m / waits until m is free
    lock_guard<mutex> lg(m);
    balance += money;
    cout << "Amount added: " << money << endl;
    cout << "Current Balance: " << balance << endl;

    // notifies the condition variable cv
    cv.notify_one();
}

void withdrawMoney(int money)
{
    // locks the mutex
    unique_lock<mutex> ul(m);

    // implicitly unlocks the mutex m while waiting for a notification
    cv.wait(ul, [] {
        return balance != 0;
    });
    // if the predicate is false, cv will continue to wait
    // if the predicate is true, ul will reacquire the lock on m

    if (balance >= money)
    {
        balance -= money;
        cout << "Amount Deducted: " << money << endl;
    }
    else
    {
        cout << "Money couldn't be deducted, current balance is less than " << money << endl;
    }
    cout << "The current balance is: " << balance << endl;
}

int main()
{
    // forcing withdraw thread first, but will deposit first
    thread t1(withdrawMoney, 400);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    thread t2(depositMoney, 500);
    t1.join();
    t2.join();

    return 0;
}
