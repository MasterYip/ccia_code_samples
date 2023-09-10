/**
 * @file listing_2.5.cpp
 * @author Master Yip (2205929492@qq.com)
 * @brief Returning a std::thread from a function
 * @version 0.1
 * @date 2023-09-10
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <thread>

void some_function()
{
    for (int i = 0; i < 1000000; ++i)
    {
        printf("some_function: %d\n", i);
    }
}

void some_other_function(int)
{
    for (int i = 0; i < 1000000; ++i)
    {
        printf("some_other_function: %d\n", i);
    }
}

std::thread f()
{
    void some_function();
    return std::thread(some_function);
}
std::thread g()
{
    void some_other_function(int);
    std::thread t(some_other_function, 42);
    return t;
}

int main()
{
    std::thread t1 = f();
    t1.join();
    std::thread t2 = g();
    t2.join();

    // Or
    // std::thread t1 = f();
    // std::thread t2 = g();
    // t1.join();
    // t2.join();
}
