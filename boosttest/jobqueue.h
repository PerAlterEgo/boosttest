//
//  jobqueue.h
//  boosttest
//

#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/condition.hpp>

#include <memory>
#include <vector>

class jobqueue {
public: 
    typedef boost::function<void()> func_type;
    
    jobqueue(size_t);
    ~jobqueue();
    
    void add(func_type);
    
    void wait_until_done();

    void process();
    
private:
    bool has_changed_state() const;
    bool no_more_jobs() const;
    bool is_active() const;
    
    boost::mutex _job_mutex;
    std::list<func_type> _jobs_todo;
    
    std::vector<boost::thread*> _threads;
    
    boost::condition_variable _new_job;
    boost::condition_variable _job_complete;

    bool _shutting_down;
    volatile int _counter;
};


