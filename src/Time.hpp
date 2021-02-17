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
#include <SDL2/SDL.h>

class Time{
  
public:
    Time(int timeMS, bool repeat);
    static void update();
    bool timedAction();
    static bool timedAction(std::chrono::milliseconds time);
    static Uint32 _now;
private:
    Uint32 _timer;
    bool _loop = false;
    int _timeAdditionMS;
    static SDL_mutex* _timeMutex;
};
#endif /* Time_hpp */
