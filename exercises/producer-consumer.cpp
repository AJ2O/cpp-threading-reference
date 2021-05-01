#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <deque>
using namespace std;

mutex m;
condition_variable cv;
deque<int> buffer;
const int maxBufferSize = 50;

void producer(int val)
{
    while (val)
    {
        std::unique_lock<std::mutex> ul(m);
        cv.wait(ul, []() {
            return buffer.size() < maxBufferSize;
        });

        buffer.push_back(val);
        cout << "Produced: " << val << endl;
        val--;

        ul.unlock();
        cv.notify_one();
    }
}

void consumer()
{
    while (true)
    {
        std::unique_lock<std::mutex> ul(m);
        cv.wait(ul, []() {
            return buffer.size() > 0;
        });

        int val = buffer.back();
        buffer.pop_back();
        cout << "Consumed: " << val << endl;

        ul.unlock();
        cv.notify_one();
    }
}

int main()
{
    thread t1(producer, 100);
    thread t2(consumer);
    t1.join();
    t2.join();

    return 0;
}