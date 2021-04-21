#include <iostream>
#include <thread>
using namespace std;

// 1. Function Pointer
void fun(int x)
{
    while (x-- > 0)
    {
        cout << x << endl;
    }
}
void FunctionPointer()
{
    std::thread t1(fun, 11);
    std::thread t2(fun, 10);
    t1.join();
    t2.join();
}

// 2. Lambda Function
void Lambda()
{
    // Lambda
    /*auto fun2 = [](int x) {
        while (x-- > 0)
        {
            cout << x << endl;
        }
    };*/

    // Can be injected directly into the thread
    std::thread t([](int x) {
        while (x-- > 0)
        {
            cout << x << endl;
        }
    },
                  10);
    t.join();
}

int main()
{
    // 1. Function Pointer
    // FunctionPointer();

    // 2. Lambda
    // Lambda()
    return 0;
}