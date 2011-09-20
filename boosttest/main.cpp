//
//  main.cpp
//  boosttest
//

#include <iostream>

#include "worker.h"
#include "fib.h"
#include "jobqueue.h"

void test1() {
    worker<int> w1(boost::bind<int>(&calculatefib, 7));
    worker<int> w2(boost::bind<int>(&calculatefib, 8));
    
    worker<int> w3(boost::bind<int>(&fib_job::calc, boost::shared_ptr<fib_job>(new fib_job(11))));
    
    int sum = w1.get() + w2.get() + w3.get();
    
    std::cout << "Done, sum=" << sum << std::endl;
}

void test2() {
    {
        jobqueue jobs(3);
    
        jobs.add(boost::bind<int>(&calculatefib, 7));
        jobs.add(boost::bind<int>(&calculatefib, 8));
        jobs.add(boost::bind<int>(&calculatefib, 12));
    }
}

int main (int argc, const char * argv[])
{
    test1();
    test2();
    return 0;
}

