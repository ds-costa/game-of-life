#include "Grid.hpp"

void Grid::Update() {
    // Births: Each dead cell adjacent to exactly three live neighbors will become live in the next generation.
    // Death by isolation: Each live cell with one or fewer live neighbors will die in the next generation.
    // Death by overcrowding: Each live cell with four or more live neighbors will die in the next generation.
    // Survival: Each live cell with either two or three live neighbors will remain alive for the next generation.
    for(int x = 0; x < GRID_ROWS; x++) {
        for(int y = 0; y < GRID_COLS; y++) {
            State isCellAlive = previousState[x][y];
            int neighborsQuantity = GetCellNeighborsQuantity(x, y);
            if(!isCellAlive && neighborsQuantity == 3) {
                SetCellState(x, y, ALIVE);
            }
            else if(neighborsQuantity <= 1 || neighborsQuantity >= 4) {
                SetCellState(x, y, DEAD);
            }
        }
    }
    SaveState();
}

void Grid::Draw() {

    Vector2 offset = {0, 0};

    if(hasGridLines) {
        DrawLine(
            initialPosition.x + offset.x, initialPosition.y + offset.y,
            initialPosition.x + offset.x, initialPosition.y + GRID_ROWS * GRID_CELL_HEIGHT,
            GRAY
        );
    }

    for(int x = 0; x < GRID_ROWS; x++) {
        for(int y = 0; y < GRID_COLS; y++) {

            mousePosition = GetMousePosition();
            bool isMouseOver = CheckCollisionPointRec(mousePosition, (Rectangle){initialPosition.x + offset.x, initialPosition.y + offset.y, (float)GRID_CELL_WIDTH, (float)GRID_CELL_HEIGHT});

            if(isMouseOver) {
                DrawRectangle(initialPosition.x + offset.x, initialPosition.y + offset.y, GRID_CELL_WIDTH, GRID_CELL_HEIGHT, RED);

                if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                    SetCellState(x, y, true);
                    SaveState();
                }
                else if(IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
                    SetCellState(x, y, false);
                    SaveState();
                }
            }
            else {
                DrawRectangle(initialPosition.x + offset.x, initialPosition.y + offset.y, GRID_CELL_WIDTH, GRID_CELL_HEIGHT, actualState[x][y] ? BLUE : WHITE);
            }

            offset.x += GRID_CELL_WIDTH;
            // Vertical lines
            if(hasGridLines) {
                DrawLine(
                    initialPosition.x + offset.x, initialPosition.y + offset.y,
                    initialPosition.x + offset.x, initialPosition.y + GRID_ROWS * GRID_CELL_HEIGHT,
                    GRAY
                );
            }
        }
        offset.x = 0;
        offset.y += GRID_CELL_HEIGHT;
        // Horizontal lines
        if(hasGridLines) {
            DrawLine(
                initialPosition.x + offset.x, initialPosition.y + offset.y,
                initialPosition.x + GRID_COLS * GRID_CELL_WIDTH, initialPosition.y + offset.y,
                GRAY
            );
        }
    }
}

void Grid::Clear() {
    for(int x = 0; x < GRID_ROWS; x++) {
        for(int y = 0; y < GRID_COLS; y++) {
            previousState[x][y] = false;
            actualState[x][y] = false;
        }
    }
}

void Grid::SetCellState(int x, int y, bool state) {
    actualState[x][y] = state;
}

void Grid::SaveState() {
    for(int x = 0; x < GRID_ROWS; x++) {
        for(int y = 0; y < GRID_COLS; y++) {
            previousState[x][y] = actualState[x][y];
        }
    }
}

bool getCellState(int x, int y, std::array<std::array<State, GRID_COLS>, GRID_ROWS> board) {
    int a = x;
    int b = y;

    if (x < 0) {
        a = GRID_COLS - 1;
    }
    if (y < 0) {
        b = GRID_ROWS - 1;
    }
    if (x > GRID_ROWS - 1) {
        a = 0;
    }
    if (y > GRID_COLS - 1) {
        b = 0;
    }

    return board[a][b];
}


int Grid::GetCellNeighborsQuantity(int x, int y) {
    std::array<Vector2i, 8> positions = {
        Vector2i{x - 1, y - 1},
        Vector2i{x    , y - 1},
        Vector2i{x + 1, y - 1},
        Vector2i{x + 1, y    },
        Vector2i{x + 1, y + 1},
        Vector2i{x    , y + 1},
        Vector2i{x - 1, y + 1},
        Vector2i{x - 1, y    },
    };

    return std::count_if(positions.begin(), positions.end(), [&](auto point) {
        return getCellState(point.x, point.y, previousState);
    });
}