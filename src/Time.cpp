//
//  Time.cpp
//  This Is a Game
//
//  Created by Ricardo Marginador on 25/01/21.
//

#include "Time.hpp"


//TODO: Could use a delegate to make a generic way to call instead of return, but not sure how tu use a delegate here
bool Time::timedAction(std::chrono::milliseconds time ){
    
    auto timer = std::chrono::system_clock::now() + time;
    
    while(true){
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        
        
        if(timer < std::chrono::system_clock::now()){
            return true;
        }
    }
    return false;
}
