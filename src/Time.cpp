//
//  Time.cpp
//  This Is a Game
//
//  Created by Ricardo Marginador on 25/01/21.
//

#include "Time.hpp"


Uint32 Time::_now;
SDL_mutex* Time:: _timeMutex= SDL_CreateMutex();
Time::Time(int timeMS, bool repeat){
    _timeAdditionMS = timeMS;
    _timer = SDL_GetTicks();
    _loop = repeat;
    //if(_timeMutex == nullptr)_timeMutex = SDL_CreateMutex();
}

//update static now reference, getting now directly from a thread using chrono was sometimes causing expection
void Time::update(){
    
    Time::_now = SDL_GetTicks();
}
bool Time::timedAction(){
    
    SDL_LockMutex(_timeMutex);
    int elapsed = (_timer - _now);
    SDL_UnlockMutex(_timeMutex);
     if(elapsed<=0)
    {
        if(_loop) _timer = _now + _timeAdditionMS;
        return true;
    }else{
        return false;
    }
}
//TODO: Could use a delegate to make a generic way to call instead of return, but not sure how tu use a delegate here
bool Time::timedAction(std::chrono::milliseconds time ){
    
    auto timer = std::chrono::high_resolution_clock::now() + time;
    
    while(true){
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        if(timer < std::chrono::high_resolution_clock::now()){
            timer = std::chrono::high_resolution_clock::now() + time;
            return true;
        }
    }
    return false;
}
