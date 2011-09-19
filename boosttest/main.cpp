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
    boost::this_thread::sleep(boost::posix_time::milliseconds(10)); 
    return n <= 1 ? 1 : calculatefib(n-1)+calculatefib(n-2);
}


int main (int argc, const char * argv[])
{
    boost::packaged_task<int> task(boost::bind<int>(&calculatefib, 12));
    boost::unique_future<int> future = task.get_future();    
    boost::thread worker_thread(boost::move(task));

    boost::packaged_task<int> task2(boost::bind<int>(&calculatefib, 12));
    boost::unique_future<int> future2 = task2.get_future();    
    boost::thread worker_thread2(boost::move(task2));

    int aa = future.get() + future2.get();
    
    worker_thread.join();
    return 0;
}

