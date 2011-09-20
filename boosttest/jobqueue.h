//
//  jobqueue.h
//  boosttest
//

#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>

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
    boost::mutex _mutex;
    std::list<func_type> _jobs_todo;
    std::auto_ptr<std::vector<boost::thread> > _threads;
};


