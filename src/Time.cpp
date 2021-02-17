//
//  Time.cpp
//  This Is a Game
//
//  Created by Ricardo Marginador on 25/01/21.
//

#include "Time.hpp"



Time::Time(std::chrono::milliseconds time, bool repeat){
    _timeAddition = time;
    _timer = std::chrono::system_clock::now();
    _loop = repeat;
}

bool Time::timedAction(){
    
    auto now = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(_timer - now);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    if(elapsed.count() < 0)
    {
        if(_loop) _timer = now + _timeAddition;
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
