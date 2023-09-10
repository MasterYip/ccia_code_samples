/**
 * @file listing_2.3.cpp
 * @author Master Yip (2205929492@qq.com)
 * @brief Using RAII to wait for a thread to complete (Thread Guard)
 * @version 0.1
 * @date 2023-09-10
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <thread>

class thread_guard
{
    std::thread &t;

public:
    explicit thread_guard(std::thread &t_) : t(t_)
    {
    }
    ~thread_guard()
    {
        if (t.joinable())
        {
            t.join();
        }
    }
    thread_guard(thread_guard const &) = delete;
    thread_guard &operator=(thread_guard const &) = delete;
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
        // Sleep 10ms
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void f()
{
    int some_local_state;
    func my_func(some_local_state);
    std::thread t(my_func);
    thread_guard g(t); // RAII Thread guard

    do_something_in_current_thread();
}

int main()
{
    f();
}
