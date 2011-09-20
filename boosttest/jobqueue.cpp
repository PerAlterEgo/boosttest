//
//  jobqueue.cpp
//  boosttest
//

#include "jobqueue.h"
#include <boost/function.hpp>
#include <boost/bind.hpp>

jobqueue::jobqueue(size_t nr_threads) : _threads(new std::vector<boost::thread>[nr_threads]) {
    for (size_t ii=0 ; ii<nr_threads ; ++ii) {
        func_type fun(boost::bind(&jobqueue::process, this));
        (*_threads)[ii] = boost::thread(fun);
    }
}

jobqueue::~jobqueue() {
    wait_until_done();
}

void jobqueue::wait_until_done() {
    
}

void jobqueue::add(func_type f) {
    boost::mutex::scoped_lock lk(_mutex);
    _jobs_todo.push_back(f);
}


void jobqueue::process() {
    
}

