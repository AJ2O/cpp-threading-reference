#include <iostream>
#include <thread>
#include <ctime>
using namespace std;
typedef unsigned long long ull;

ull evenSum = 0;
ull oddSum = 0;

void findEvenSum(ull start, ull end)
{
    for (ull i = start; i <= end; i++)
    {
        if (i % 2 == 0)
        {
            evenSum += i;
        }
    }
}

void findOddSum(ull start, ull end)
{
    for (ull i = start; i <= end; i++)
    {
        if (i % 2 == 1)
        {
            oddSum += i;
        }
    }
}

void RunUnthreaded(ull start, ull end)
{
    evenSum = 0;
    oddSum = 0;
    findOddSum(start, end);
    findEvenSum(start, end);
}

void Run_FunctionPointer(ull start, ull end)
{
    evenSum = 0;
    oddSum = 0;

    // Syntax: Pointer (fnc, args ...)
    std::thread t1(findEvenSum, start, end);
    std::thread t2(findOddSum, start, end);

    // Join the threads to get the results
    t1.join();
    t2.join();
}

int main()
{
    ull start = 1, end = 1000000000;

    // Unthreaded
    cout << "======= Unthreaded =======" << endl;
    time_t startTime, endTime;
    time(&startTime);
    RunUnthreaded(start, end);
    time(&endTime);

    cout << "EvenSum : " << evenSum << endl;
    cout << "OddSum : " << oddSum << endl;
    cout << "Time required: " << difftime(endTime, startTime) << " seconds" << endl
         << endl;

    // Parallel Threads (Function Pointers)
    cout << "======= Function Pointers =======" << endl;
    time(&startTime);
    Run_FunctionPointer(start, end);
    time(&endTime);

    cout << "EvenSum : " << evenSum << endl;
    cout << "OddSum : " << oddSum << endl;
    cout << "Time required: " << difftime(endTime, startTime) << " seconds" << endl;

    return 0;
}
