#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <vector>
#include <memory>

#include "Grid.hpp"

#include "../lib/raylib/raylib.h"
#include "../lib/raylib/raymath.h"

using Seconds = float;


class Game {
public:
    
    static const int FRAME_RATE = 60;
    
    Game(int windowWidth, int windowHeight, std::string title);
    ~Game();
    void Run();

private:

    // Window
    int windowWidth, windowHeight;
    
    // Assets
    Font commodore;
    
    // Simulation control
    bool isRunning = false;
    float simulationSpeed = 1.0;     
    Seconds timer;
    Seconds updateRate = 0.1f;
    
    // Simulation objects
    Grid grid;

    // Game loop
    void Update(float dt);
    void Draw();
};
#endif