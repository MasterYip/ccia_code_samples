/**
 * @file listing_2.1.cpp
 * @author Master Yip (2205929492@qq.com)
 * @brief A function that returns while a thread still has access to local variables
 * @version 0.1
 * @date 2023-09-09
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <thread>
#include <time.h>
void do_something(int &i)
{
    ++i;
    printf("do_something: %d\n", i);
}

struct func
{
    int &i;

    func(int &i_) : i(i_) {}

    void operator()()
    {
        for (unsigned j = 0; j < 1000000; ++j)
        {
            do_something(i); // Potential access to dangling reference
        }
    }
};

void oops()
{
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread my_thread(my_func);
    my_thread.detach();
}

int main()
{
    printf("main\n");
    oops();
    // Sleep for 1s
    struct timespec ts;
    ts.tv_sec = 0.05;
    ts.tv_nsec = 0;
    nanosleep(&ts, NULL);
    printf("main end\n");
}
// New thread might still be running
// (The printed value of i is unstable after main() returns)
/* example output:
main
do_something: 1
do_something: 2
do_something: 3
do_something: 4
do_something: 5
do_something: 6
do_something: 7
do_something: 8
do_something: 9
do_something: 10
do_something: 11
do_something: 12
do_something: 13
do_something: 14
do_something: 15
do_something: 16
do_something: 17
do_something: 18
do_something: 19
do_something: 20
do_something: 21
do_something: 22
main end
do_something: 1
do_something: 1
do_something: 2
do_something: 3
do_something: 4
do_something: 5
do_something: 5
do_something: 1
do_something: 2
do_something: 3
do_something: 4
do_something: 4
do_something: 5
*/