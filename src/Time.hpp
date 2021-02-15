//
//  Time.hpp
//  This Is a Game
//
//  Created by Ricardo Marginador on 25/01/21.
//

#ifndef Time_hpp
#define Time_hpp

#include <stdio.h>
#include <chrono>
#include <thread>

class Time{
  
public:
    static bool timedAction(std::chrono::milliseconds time);
};
#endif /* Time_hpp */
