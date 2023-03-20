#include "Game.hpp"
#define RAYGUI_IMPLEMENTATION
#include "../lib/raylib/raygui.h"

Game::Game(int windowWidth, int windowHeight, std::string title):
    windowWidth(windowWidth),
    windowHeight(windowHeight),
    timer(0) {

    InitWindow(windowWidth, windowHeight, title.c_str());
    SetTargetFPS(Game::FRAME_RATE);

    commodore = LoadFont("resources/fonts/Commodore.ttf");
}

Game::~Game() {
    CloseWindow();
}

void Game::Update(float deltaTime) {
    if(isRunning) {
        timer += deltaTime;
        if(timer - (UPDATE_RATE/simulationSpeed) >= 0) {
            grid.Update();
            timer = 0;
        }
    }
}

void Game::Draw() {
    // GUI controls
    DrawTextEx(commodore, std::string(std::string("FPS: ") + std::to_string(GetFPS())).c_str(), {0, 0}, 12, 2, WHITE);
    DrawTextEx(commodore, ("[" + std::to_string((int)GetMousePosition().x) + "," + std::to_string((int)GetMousePosition().y) + "]").c_str(), {0, 14}, 12, 2, WHITE);
    DrawTextEx(commodore, ((!isRunning) ? "Paused" : "Running"), {40, 240}, 12, 2, WHITE);

    // Game
    grid.Draw();

    // GUI controls
    simulationSpeed = GuiSlider((Rectangle){ 40, 40, 120, 20 }, "Speed", NULL, simulationSpeed, 1, 4);

    if(GuiButton((Rectangle){ 40, 80, 120, 20 }, "Play / Pause") ) {
        isRunning = !isRunning;
    }
    if(GuiButton((Rectangle){ 40, 120, 120, 20 }, "Step")) {
        if(!isRunning) {
            grid.Update();
            timer = 0;
        }
    }
    if(GuiButton((Rectangle){ 40, 160, 120, 20 }, "Grid Lines On/Off")) {
        grid.hasGridLines = !grid.hasGridLines;
    }
    if(GuiButton((Rectangle){ 40, 200, 120, 20 }, "Clear Grid")) {
        grid.Clear();
    }
}

void Game::Run() {
    while(!WindowShouldClose()) {
        Update(GetFrameTime());
        BeginDrawing();
        ClearBackground(BLACK);
        Draw();
        EndDrawing();
    }
}