//
//  main.cpp
//  boosttest
//
//  Created by Per Ersson on 9/18/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <vector>

#include <boost/thread/thread.hpp>
#include <boost/thread/future.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <iostream>

int calculatefib(int d1)
{
    return d1;
}


class Worker {
public:
    Worker(boost::function<int()> f) : _function(f) {}
    void operator()();

    
private:
    boost::function<int()> _function;
};

void Worker::operator()() {
    _function();
}


int main (int argc, const char * argv[])
{
    boost::function<int()> f = boost::bind<int>(&calculatefib, 0);
    
    Worker worker(f);
    boost::thread worker_thread(worker);
    
    // insert code here...
    std::cout << "Hello, World!\n";
    
    worker_thread.join();
    return 0;
}

