#include "minirpc/comm/log.h"
#include <functional>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;
class Foo
{
private:
    int curr_num;
    std::mutex mut;
    std::condition_variable data_cond_1, data_cond_2;

public:
    Foo() : curr_num(0)
    {
    }

    void first(function<void()> printFirst)
    {
        std::unique_lock<std::mutex> lk(mut);
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        lk.unlock();
        curr_num = 1;
        data_cond_1.notify_one();
    }

    void second(function<void()> printSecond)
    {
        std::unique_lock<std::mutex> lk(mut);
        data_cond_1.wait(lk, [&]
                         { return curr_num == 1; });
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        lk.unlock();
        curr_num = 2;
        data_cond_2.notify_one();
    }

    void third(function<void()> printThird)
    {
        std::unique_lock<std::mutex> lk(mut);
        data_cond_2.wait(lk, [&]
                         { return curr_num == 2; });
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
        lk.unlock();
        curr_num = 3;
    }
};
int main()
{
    // Solution s;
    int num;
    cin >> num;
    return 0;
}