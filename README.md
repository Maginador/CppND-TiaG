# CPP Nanodegree - This is a Game
-------

## What is this thing?
This is a Game as you can see... My First game using **CPP + SDL**, probably not the last. Game done as capstone project for Udacity Cpp Nanodegree.

## Overview 
The project is a basic game engine writen with C++ ans SDL. 
The core developed game is a PvZ clone (with some twists and simplifications)

![Game Print](print01.png?raw=true "Game Print")

Your goal is to survive as much as possible. 
You can move using keyboard arrows and press f to place a tower in a slot 
Monsters will appear along the way and you need to kill them!!!

## Platforms 
The project is being developed using Mac OS and Linux. **Linux** is the main platform for the purpose of the **Nanodegree**
`_Android and Windows_ are future candidates for long term`

## Building the Game
    Install the dependency libraries 
    create a build folder 
    copy and paste the folders fonts and assets inside it 
    open terminal inside build folder 
    run "cmake .." 
    run "make"
    run "./cpp-tiag" to play the game 

## Using the Engine 
    To be defined 
    
## Releases 
    To be defined
    

## Dependencies 

* [SDL2](https://www.libsdl.org/)
* [SDL2_image](https://www.libsdl.org/projects/SDL_image/)
* [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/)

## Rubric

The project chosen as capstone is a game using SDL. Details about the game can be seen above. 
You can see bellow each rubric followed

  * Compiling and Testing : The project was tested in the workspace provided by Udacity
  * Loops, Functions, I/O : You will find loops for game loop, for lists iteration. Functions are used all over the place. User input and file acquisition is done using SDL lib calls 
  * Object Oriented Programming : I divided the project in a granularity that made sense to me, GameObjects, Renderables, Physics specific stuff and so on. I created internal classes for similar objects (such as sub classes of Character) but each of them could be a separate one. I used classes Hierarchy, casting, and so on. 
  * Memory Management : I tried to avoid raw pointers, I started using raw pointers all over the place and got back to convert them into shared_ptr and unique_ptr when possible, I will still work on other areas, my plan is to remove almost 100% of raw pointers as recommended, but I want to do that gradually and smoothly.
  * Concurrency : I used SDL Thread system for that, Enemies are spawned using thread. I added mutexes to avoid condition race, some threads were removed due to critical issues but I am still investigating where it is worth it to implement more threads.


