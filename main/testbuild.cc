#include "minirpc/comm/log.h"
#include <functional>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;
class FooBar
{
private:
    int n;
    condition_variable cv;
    mutex mut;
    bool turn = false;

public:
    FooBar(int n)
    {
        this->n = n;
    }

    void foo(function<void()> printFoo)
    {

        for (int i = 0; i < n; i++)
        {
            unique_lock<mutex> lk(mut);
            cv.wait(lk, [&]
                    { return !turn; });
            // printFoo() outputs "foo". Do not change or remove this line.
            printFoo();
            turn = true;
            lk.unlock();
            cv.notify_one();
        }
    }

    void bar(function<void()> printBar)
    {

        for (int i = 0; i < n; i++)
        {
            unique_lock<mutex> lk(mut);
            cv.wait(lk, [&]
                    { return turn; });
            // printBar() outputs "bar". Do not change or remove this line.
            printBar();
            turn = false;
            lk.unlock();
            cv.notify_one();
        }
    }
};
int main()
{
    int n = 3;
    FooBar s(n);
    cout << "out:\n";
    thread t1(&FooBar::foo, &s, []
              { cout << "foo"; });
    thread t2(&FooBar::bar, &s, []
              { cout << "bar"; });
    t1.join();
    t2.join();
    return 0;
}