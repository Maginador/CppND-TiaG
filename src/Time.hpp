//
//  Time.hpp
//  This Is a Game
//
//  Created by Ricardo Marginador on 25/01/21.
//

#ifndef Time_hpp
#define Time_hpp

#include <iostream>
#include <chrono>
#include <thread>

class Time{
  
public:
    Time(std::chrono::milliseconds time, bool repeat);
    bool timedAction();
    static bool timedAction(std::chrono::milliseconds time);
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> _timer;
    bool _loop = false;
    std::chrono::milliseconds _timeAddition;
};
#endif /* Time_hpp */
