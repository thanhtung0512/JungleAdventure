#ifndef IMP_TIMER_H
#define IMP_TIMER_H

class impTimer{
    public :
    impTimer();
    ~impTimer();

    void start();
    void stop ();
    void paused ();
    void resume();
    int  getTicks();

    bool isStarted_();
    bool isPaused_();


    private :

    int startTick ; 
    int pauseTick ; 
    bool isPaused ; 
    bool isStarted ; 


};


#endif 