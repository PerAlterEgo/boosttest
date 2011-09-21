//
//  fib.cpp
//  boosttest
//

#include "fib.h"

#include <boost/thread.hpp>

boost::mutex m_mutex;

int calculatefib(int n)
{
    return n <= 1 ? 1 : calculatefib(n-1)+calculatefib(n-2);
}

fib_job::fib_job(int n) : _n(n) {}

int fib_job::calc() const {
    return calculatefib(_n);
}

