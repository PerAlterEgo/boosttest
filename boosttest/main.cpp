//
//  main.cpp
//  boosttest
//

#include <iostream>

#include "worker.h"
#include "fib.h"

int main (int argc, const char * argv[])
{
    worker<int> w1(boost::bind<int>(&calculatefib, 7));
    worker<int> w2(boost::bind<int>(&calculatefib, 8));

    worker<int> w3(boost::bind<int>(&fib_job::calc, boost::shared_ptr<fib_job>(new fib_job(11))));
    
    int aa = w1.get() + w2.get();

    std::cout << "Done" << std::endl;
    return 0;
}

