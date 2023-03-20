#ifndef GRID_HPP
#define GRID_HPP

#include <array>
#include "Modulo.hpp"
#include "../lib/raylib/raylib.h"
#include "../lib/raylib/raymath.h"

static const int GRID_ROWS{41};
static const int GRID_COLS{41};
static const int GRID_CELL_WIDTH{15};
static const int GRID_CELL_HEIGHT{15};

using State = bool;

class Grid {

public:
    bool hasGridLines = true;

    void Update();
    void Draw();
    void Clear();

private:

    std::array<
        std::array<State, GRID_COLS>,
        GRID_ROWS
    > previousState{false};

    std::array<
        std::array<State, GRID_COLS>,
        GRID_ROWS
    > actualState{false};

    Vector2 mousePosition{0, 0};

    // Cell draw data
    Vector2 initialPosition{350, 30};

    int GetCellNeighborsQuantity(int x, int y);
    inline void SetCellState(int x, int y, State state);
    void SaveState();
};

#endif