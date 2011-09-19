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

boost::mutex m_mutex;

int calculatefib(int n)
{
    boost::this_thread::sleep(boost::posix_time::milliseconds(10)); 
    {    
        boost::mutex::scoped_lock l(m_mutex);
        std::cout << boost::this_thread::get_id() << ": fib(" << n << ")" << std::endl;
    }
    return n <= 1 ? 1 : calculatefib(n-1)+calculatefib(n-2);
}

class fib_job {
public:
    fib_job(int n);
    
    int calc() const;    
    
private:
    int _n;
};

fib_job::fib_job(int n) : _n(n) {}

int fib_job::calc() const {
    return calculatefib(_n);
}


template<typename T>
class worker {
public:
    worker(boost::function<T ()> f);
    ~worker();
    
    T get();

private:
    boost::packaged_task<T> _pack_task;
    boost::unique_future<T> _future;
    boost::thread _thread;
};

template<typename T>
worker<T>::worker(boost::function<T ()> f) : _pack_task(f), _future(_pack_task.get_future()), _thread(boost::move(_pack_task)) {}

template<typename T>
worker<T>::~worker() {
    _future.get();
    _thread.join();
}

template<typename T>
T worker<T>::get() {
    return _future.get();
}

int main (int argc, const char * argv[])
{
    worker<int> w1(boost::bind<int>(&calculatefib, 7));
    worker<int> w2(boost::bind<int>(&calculatefib, 8));

    worker<int> w3(boost::bind<int>(&fib_job::calc, boost::shared_ptr<fib_job>(new fib_job(11))));
    
    int aa = w1.get() + w2.get();

    std::cout << "Done" << std::endl;
    return 0;
}

