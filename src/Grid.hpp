#ifndef GRID_HPP
#define GRID_HPP

#include "Modulo.hpp"
#include "../lib/raylib/raylib.h"
#include "../lib/raylib/raymath.h"

static const int GRID_ROWS = 41;
static const int GRID_COLS = 41;

using State = bool;

class Grid {

public:
    bool hasGridLines = true;

    void Update();
    void Draw();
    void Clear();

private:

    State previousState[GRID_ROWS][GRID_COLS]{false};
    State actualState[GRID_ROWS][GRID_COLS]{false};
    Vector2 mousePosition{0, 0};

    // Cell draw data
    Vector2 initialPosition{350, 30};
    // Cell data
    int cellWidth{15};
    int cellHeight{15};

    int GetCellNeighborsQuantity(int x, int y);
    inline void SetCellState(int x, int y, State state);
    void SaveState();
};

#endif