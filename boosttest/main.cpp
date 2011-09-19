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

int calculatefib(int n)
{
    return n <= 1 ? 1 : calculatefib(n-1)+calculatefib(n-2);
}


class Worker {
public:
    Worker(boost::function<int()> f) : _function(f) {}
    void operator()();

    
private:
    boost::function<int()> _function;
};

void Worker::operator()() {
    std::cout << "Thread: " << _function() << std::endl;
}


int main (int argc, const char * argv[])
{
    boost::function<int()> f = boost::bind<int>(&calculatefib, 12);
    boost::packaged_task<int> task(f);
    boost::unique_future<int> future = task.get_future();
    
    Worker worker(f);
    boost::thread worker_thread(worker);
    
    // insert code here...
    std::cout << "Hello, World!\n";
    
    task();
    
    int aa = future.get();
    
    worker_thread.join();
    return 0;
}

