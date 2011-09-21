//
//  jobqueue.cpp
//  boosttest
//

#include "jobqueue.h"
#include <boost/function.hpp>
#include <boost/bind.hpp>

#include <iostream>

#include <assert.h>

jobqueue::jobqueue(size_t nr_threads) : _counter(0), _shutting_down(false) {
    boost::mutex::scoped_lock lk(_job_mutex);
    _threads.resize(nr_threads);
    for (size_t ii=0 ; ii<_threads.size() ; ++ii) {
        func_type fun(boost::bind(&jobqueue::process, this));
        _threads[ii] = new boost::thread(fun);
    }
}

jobqueue::~jobqueue() {
    wait_until_done();
    
    for (size_t ii=0 ; ii<_threads.size() ; ++ii) {
        _threads[ii]->join();
        delete _threads[ii];
    }

}

void jobqueue::wait_until_done() {
    
    boost::mutex::scoped_lock lock(_job_mutex);
    
    if (_jobs_todo.size() > 0) {
        _job_complete.wait(lock, boost::bind(&jobqueue::no_more_jobs, this));
    }
    
    _shutting_down = true;
    
    // Wake up all threads
    _new_job.notify_all();
}
 

void jobqueue::add(func_type f) {
    boost::mutex::scoped_lock lk(_job_mutex);
    _jobs_todo.push_back(f);
    lk.unlock();
    _new_job.notify_one(); 
}

bool jobqueue::has_changed_state() const {
    return _jobs_todo.size() > 0 || _shutting_down;
}

bool jobqueue::no_more_jobs() const {
    return _jobs_todo.size() == 0;
}

bool jobqueue::is_active() const {
    return _shutting_down == false;
}

void jobqueue::process() {
    while(is_active()) {
        boost::mutex::scoped_lock lock(_job_mutex);
        
        assert (_counter == 0);
        
        _new_job.wait(lock, boost::bind(&jobqueue::has_changed_state, this));
        
        if (is_active()) {
            assert (_counter == 0);
            ++_counter;
            
            func_type fun = *_jobs_todo.begin();
            _jobs_todo.pop_front();
            
            assert (_counter == 1);
            --_counter;
            
            lock.unlock();
            
            fun();
            
            _job_complete.notify_one();
            
        }
    }
}

