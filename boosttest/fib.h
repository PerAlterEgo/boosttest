//
//  fib.h
//  boosttest
//

extern int calculatefib(int n);

class fib_job {
public:
    fib_job(int n);
    
    int calc() const;    
    
private:
    int _n;
};

