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

void test2(int nr_threads, int nr_jobs) {
    {
        jobqueue jobs(nr_threads);

        for (int ii=0 ; ii<nr_jobs*100 ; ++ii) {
            jobs.add(boost::bind<int>(&calculatefib, 30));
        }
    }
}

int main (int argc, const char * argv[])
{
    int nr_threads = argc > 1 ? atoi(argv[1]) : 4;
    int nr_jobs =  argc > 2 ? atoi(argv[2]) : 16;
    
    test2(nr_threads, nr_jobs);
    //test1();
    return 0;
}

