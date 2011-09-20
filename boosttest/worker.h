//
//  worker.h
//  boosttest
//

#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/thread/future.hpp>


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

