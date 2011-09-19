//
//  main.cpp
//  boosttest
//
//  Created by Per Ersson on 9/18/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <boost/thread/thread.hpp>
#include <iostream>

class Worker {
public:
    void operator()();

};

void Worker::operator()() {
    std::cout << "Thread!\n";
}

int main (int argc, const char * argv[])
{
    Worker worker;
    boost::thread worker_thread(worker);
    
    // insert code here...
    std::cout << "Hello, World!\n";
    
    worker_thread.join();
    return 0;
}

