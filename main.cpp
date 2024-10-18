#include "raylib.h"
#include <ctime>
#include <iostream>

void frameDelay() {
  time_t before = time(0);
  while (difftime(time(0), before) < 1)
    ;
}

enum TileType { EMPTY = 0, BLOCK = 1, SAND = 2 };

bool IsBlockBelow(int tilemap[][18], int rows, int cols, int row, int col) {
  return (row + 1 < rows) && (tilemap[row + 1][col] == BLOCK);
}

bool IsGapRight(int tilemap[][18], int rows, int cols, int row, int col) {
  return (row + 1 < rows) && (tilemap[row + 1][col + 1] == EMPTY);
}

bool IsGapLeft(int tilemap[][18], int rows, int cols, int row, int col) {
  return (row + 1 < rows) && (tilemap[row + 1][col - 1] == EMPTY);
}

int main() {
  const int tileHeight = 32;
  const int tileWidth = 32;

  const int rows = 18;
  const int cols = 18;

  int tilemap[rows][cols]{
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //
    { 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0 }, //
    { 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0 }, //
    { 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0 }, //
    { 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0 }, //
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //
    { 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 }, //
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //
  };

  InitWindow(576, 576, "falling sand");
  SetTargetFPS(60);

  while (WindowShouldClose() == false) {
    BeginDrawing();
    ClearBackground(BLACK);

    frameDelay();

    for (int row = rows - 1; row >= 0; row--) {
      for (int col = 0; col < cols; col++) {
        if (tilemap[row][col] == SAND) {
          // SAND FALLING LOGIC
          if (!IsBlockBelow(tilemap, rows, cols, row, col) && tilemap[row + 1][col] == EMPTY) {
            tilemap[row + 1][col] = SAND;
            tilemap[row][col] = EMPTY;
          } else {
            if (IsGapRight(tilemap, rows, cols, row, col) && (tilemap[row][col + 1] == EMPTY) &&
                tilemap[row + 1][col] != EMPTY) {
              if (IsGapRight(tilemap, rows, cols, row, col) && tilemap[row + 1][col + 1] == EMPTY)
                tilemap[row + 1][col + 1] = SAND;
              tilemap[row][col] = EMPTY;
            }
            if (IsGapLeft(tilemap, rows, cols, row, col) && tilemap[row][col - 1] == EMPTY &&
                tilemap[row + 1][col] != EMPTY) {
              if (IsGapLeft(tilemap, rows, cols, row, col) && tilemap[row + 1][col - 1] == EMPTY)
                tilemap[row + 1][col - 1] = SAND;
              tilemap[row][col] = EMPTY;
            }
          }
        }
      }
    }

    for (int row = 0; row < rows; row++) {
      for (int col = 0; col < cols; col++) {
        int x = col * tileWidth;
        int y = row * tileHeight;

        if (tilemap[row][col] == BLOCK) {
          DrawRectangle(x, y, tileWidth, tileHeight, WHITE);
        } else if (tilemap[row][col] == SAND) {
          DrawRectangle(x, y, tileWidth, tileHeight, YELLOW);
        }
      }
    }
    EndDrawing();
  }

  CloseWindow();
}
