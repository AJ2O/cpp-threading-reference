/*
    join    - once a thread is started, we wait for it to finish
            - double join results in program termination
            - to check if a thread can be joined, use joinable()
        
    detach  - detaches the newly created thread from the parent thread
            - double detach results in program termination
            - parent exiting -> detached threads also exit
*/

#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

void run(int count)
{
    cout << "Running..." << endl;
    std::this_thread::sleep_for(chrono::seconds(count));
}

int main()
{
    // Join
    int x = 10;
    std::thread t(run, x);
    cout << "join -- main()" << endl;
    t.join();

    // will compile fine, but will result in runtime error
    // t.join();

    // check if joinable
    if (t.joinable())
    {
        t.join();
    }
    cout << "join -- main() after " << x << " seconds" << endl;

    // Detach
    std::thread td(run, x);
    cout << "detach -- main()" << endl;
    td.detach();
    cout << "detach -- main() before " << x << " seconds has passed" << endl;

    return 0;
}