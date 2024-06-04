#include "a4.h"

//getInstance() is a singleton
Timer* Timer::instance_=0;
Timer* Timer::getInstance(){
    if(instance_==0){
        instance_=new Timer();
    }
    return instance_;
}

Subject::Subject(){

}
void Subject::attach(Observer* o){
    observers_.push_back(o);
}
void Subject::detach(const Observer* o){
    for (auto it=observers_.begin();it!=observers_.end();it++){
        if (*it==o){
            observers_.erase(it);
            break;
        }
    }
}
void Subject::notify(){
    //notify all the observers
    for (auto it : observers_){
        it->update();
    }
}

Under::Under(double threshold){
    threshold_=threshold;
}

void Under::update(){
    double time=Timer::getInstance()->currtime();
    if (time<threshold_){
        state_=true;
    }
    else{
        state_=false;
    }
}

bool Under::state() const{
    return state_;
}

Over::Over(double threshold){
    threshold_=threshold;
}

void Over::update(){
    double time=Timer::getInstance()->currtime();
    if (time>threshold_){
        state_=true;
    }
    else{
        state_=false;
    }
}

bool Over::state() const{
    return state_;
}

Status::Status(){
}

void Status::update(){
    bool time=Timer::getInstance()->isPaused();
    if (time){
        state_=true;
    }
    else{
        state_=false;
    }
}

bool Status::state() const{
    return state_;
}

UndoStack::UndoStack(){
}

void UndoStack::save(Memento* m){
    if (m == nullptr){
        return;
    }
    if (mementos_.size() >= 5){
        mementos_.erase(mementos_.begin());
        mementos_.push_back(m);
    }
    else{
        mementos_.push_back(m);
    }
}
Memento* UndoStack::getMemento(){
    if (mementos_.size() == 0){
        return nullptr;
    }
    Memento* m = mementos_.back();
    mementos_.pop_back();
    return m;
}
Memento::Memento(double elapsedTime, double startTime, bool isstop){
    elapsedTime_ = elapsedTime;
    startTime_ = startTime;
    isstop_ = isstop;
}

double Memento::getElapsedTime(){
    return elapsedTime_;
}

double Memento::getStartTime(){
    return startTime_;
}

bool Memento::getIsStop(){
    return isstop_;
}

Memento* Timer::createMemento(){
    //create a memento object and return it
    Memento* m = new Memento(currtime(), starttime(), isstop_);
    return m;
}




bool Timer::restoreFromMemento(Memento* m){
    /*this block of code gets the current time depending on platform
    .. you will need this to restore your timer */
    #if PLATFORM == WINDOWS
        clock_t curr=clock();
    #else
        struct timespec curr;
        clock_gettime(CLOCK_MONOTONIC_RAW, &curr);
    #endif
    if (m == nullptr){
        delete m;
        return false;
    }

    //restore the timer from the memento
    elapsedTime_ = m->getElapsedTime();
    starttime_ =curr;
    stoptime_ = curr;
    isstop_ = m->getIsStop();
    delete m;
    return true;
}




/**************************************************************/
/*   Nothing below this comment should be modified            */
/**************************************************************/

/* Timer class functions.
  start();  starts the clock running from the current time
  currtime();  returns the current time
  stop();  stops the clock without reseting its value
  reset();  stops the clock and resets the timer to 0
  isPaused(); returns true if the timer is stopped, false otherwise
*/

Timer::Timer(){
    elapsedTime_=0;
    isstop_=true;

#if PLATFORM == WINDOWS
    starttime_=0;
    stoptime_=0;    
#else
    clock_gettime(CLOCK_MONOTONIC_RAW, &starttime_);
    stoptime_=starttime_;
#endif


}
void Timer::reset(){
#if PLATFORM == WINDOWS
    starttime_=0;
    stoptime_=0;    
#else
    clock_gettime(CLOCK_MONOTONIC_RAW, &starttime_);
    stoptime_=starttime_;
#endif
    elapsedTime_=0;
    isstop_=true;
}
void Timer::start(){
#if PLATFORM == WINDOWS
    clock_t curr=clock();
    if(isstop_){
        starttime_=curr;
        isstop_=false;
    }
    else{
        starttime_=curr;   //its like hitting reset and start
        stoptime_=starttime_;
        elapsedTime_=0;
    }
#else
    struct timespec curr;
    clock_gettime(CLOCK_MONOTONIC_RAW, &curr);
    if(isstop_){
        starttime_=curr;
        isstop_=false;
    }
    else{
        clock_gettime(CLOCK_MONOTONIC_RAW, &starttime_);
        stoptime_=starttime_;
        elapsedTime_=0;
    }
#endif

}
void Timer::stop(){
#if PLATFORM == WINDOWS
    stoptime_=clock();
    elapsedTime_+=stoptime_-starttime_;
#else
    clock_gettime(CLOCK_MONOTONIC_RAW, &stoptime_);
    elapsedTime_ += (stoptime_.tv_nsec - starttime_.tv_nsec) / 1000000000.0 + 
            (stoptime_.tv_sec  - starttime_.tv_sec);
#endif
    isstop_=true;
}
double Timer::currtime(){
    double rc;
#if PLATFORM == WINDOWS
    clock_t curr=clock();
    clock_t elapse=(isstop_)?elapsedTime_:(elapsedTime_+curr-starttime_);
    rc= double(elapse)/CLOCKS_PER_SEC;
#else
    struct timespec curr;
    clock_gettime(CLOCK_MONOTONIC_RAW,&curr);
    if(isstop_){
        rc=elapsedTime_;
    }
    else{
        rc=elapsedTime_ + (curr.tv_nsec - starttime_.tv_nsec) / 1000000000.0 + 
            (curr.tv_sec  - starttime_.tv_sec);
    }    
#endif
    return rc;
}
double Timer::starttime(){
#if PLATFORM == WINDOWS
    return (double)starttime_;
#else
    return starttime_.tv_nsec/ 1000000000.0 + starttime_.tv_sec;
#endif
}
bool Timer::isPaused(){
    return isstop_;
}
