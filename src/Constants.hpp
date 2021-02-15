//
//  Constants.hpp
//  TiaG
//
//  Created by Ricardo Marginador on 14/02/21.
//

#ifndef Constants_hpp
#define Constants_hpp
#include <SDL2/SDL.h>
//Screen dimension constants
static const int SCREEN_WIDTH = 1280;
static const int SCREEN_HEIGHT = 920;


//Game Constants
static const int MOVE_INTENSITY_Y = 130;
static const int CURSOR_INIT_POSITION_Y = 150;

static const int MOVE_INTENSITY_X = 100;
static const int CURSOR_INIT_POSITION_X = 150;


static const int GRID_WIDTH = 8;
static const int GRID_HEIGHT = 5;

static const int ENEMY_SPAWN_X = CURSOR_INIT_POSITION_X + (GRID_WIDTH * MOVE_INTENSITY_X);
static const int ENEMY_SPAWN_Y = ((GRID_HEIGHT-1) * MOVE_INTENSITY_Y);

static const int SPAWNING_TIME_LOWER_RANGE = 8;
static const int SPAWNING_TIME_UPPER_RANGE = 15;

static const int FRAMES_PER_SECOND = 60;
static const int SCREEN_TICKS_PER_FRAME = 1000/FRAMES_PER_SECOND;

static const int TOWER_PRICE = 100;
//End constants area


//User Interface
static const SDL_Color ACOLOR_WHITE {255,255,255,255};
static const SDL_Color ACOLOR_BLACK {0,0,0,255};
static const SDL_Color ACOLOR_BLUE {0,0,255,255};
static const SDL_Color ACOLOR_GREEN {0,255,0,255};
static const SDL_Color ACOLOR_RED {255,0,0,255};


#endif /* Constants_hpp */