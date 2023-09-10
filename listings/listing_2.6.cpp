/**
 * @file listing_2.6.cpp
 * @author Master Yip (2205929492@qq.com)
 * @brief scoped_thread and example usage
 * @version 0.1
 * @date 2023-09-10
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <thread>
#include <utility>

class scoped_thread
{
    std::thread t;
public:
    explicit scoped_thread(std::thread t_) : t(std::move(t_))
    {
        printf("scoped_thread constructor\n");
        if (!t.joinable())
            throw std::logic_error("No thread");
    }
    ~scoped_thread()
    {
        t.join();
    }
    // Delete copy constructor
    scoped_thread(scoped_thread const &) = delete;
    scoped_thread &operator=(scoped_thread const &) = delete;
};

void do_something(int &i)
{
    ++i;
    if (i % 100000 == 0)
        printf("do_something in sub thread: %d\n", i);
}

struct func
{
    int &i;

    func(int &i_) : i(i_) {}

    void operator()()
    {
        printf("func in sub thread\n");
        for (unsigned j = 0; j < 1000000; ++j)
        {
            do_something(i);
        }
    }
};

void do_something_in_current_thread()
{
    for (int i = 0; i < 10; ++i)
    {
        printf("do_something_in_current_thread\n");
        // Sleep 1ms
        struct timespec ts;
        ts.tv_sec = 0;
        ts.tv_nsec = 1000000;
        nanosleep(&ts, NULL);
    }
}

void f()
{
    int some_local_state = 3;
    // scoped_thread t(std::thread(func(some_local_state))); // The sub thread is not running
    scoped_thread t(std::move(std::thread(func(some_local_state)))); // This is OK

    // func my_func(some_local_state);
    // std::thread th(my_func);
    // scoped_thread st(std::move(th));

    do_something_in_current_thread();
}

int main()
{
    f();
}
