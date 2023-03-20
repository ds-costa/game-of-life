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
                SetCellState(x, y, true);
            }
            else if(neighborsQuantity <= 1 || neighborsQuantity >= 4) {
                SetCellState(x, y, false);
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

int Grid::GetCellNeighborsQuantity(int x, int y) {

    int neighbors_counter = 0;
    int a = 0, b = 0;

    a = Modulo::Subtract(x, 1, GRID_ROWS);
    b = Modulo::Subtract(y, 1, GRID_ROWS);
    if(previousState[a][b]) {
        neighbors_counter++;
    }

    a = Modulo::Subtract(x, 1, GRID_ROWS);
    b = y;
    if(previousState[a][b]) {
        neighbors_counter++;
    }

    a = Modulo::Subtract(x, 1, GRID_ROWS);
    b = Modulo::Add(y, 1, GRID_ROWS);
    if(previousState[a][b]) {
        neighbors_counter++;
    }

    a = x;
    b = Modulo::Subtract(y, 1, GRID_ROWS);
    if(previousState[a][b]) {
        neighbors_counter++;
    }

    a = x;
    b = Modulo::Add(y, 1, GRID_ROWS);
    if(previousState[a][b]) {
        neighbors_counter++;
    }

    a = Modulo::Add(x, 1, GRID_ROWS);
    b = Modulo::Subtract(y, 1, GRID_ROWS);
    if(previousState[a][b]) {
        neighbors_counter++;
    }

    a = Modulo::Add(x, 1, GRID_ROWS);
    b = y;
    if(previousState[a][b]) {
        neighbors_counter++;
    }

    a = Modulo::Add(x, 1, GRID_ROWS);
    b = Modulo::Add(y, 1, GRID_ROWS);
    if(previousState[a][b]) {
        neighbors_counter++;
    }

    return neighbors_counter;
}