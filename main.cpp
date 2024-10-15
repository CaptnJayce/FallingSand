#include "raylib.h"
#include <iostream>

enum TileType { EMPTY = 0, BLOCK = 1, SAND = 2 };

bool IsBlockBelow(int tilemap[][5], int rows, int cols, int row, int col) {
  return (row + 1 < rows) && (tilemap[row + 1][col] == BLOCK);
}

int main() {
  const int tileHeight = 32;
  const int tileWidth = 32;

  const int rows = 5;
  const int cols = 5;

  int tilemap[rows][cols]{{0, 2, 0, 2, 0},
                          {0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0},
                          {0, 0, 1, 1, 0},
                          {0, 0, 0, 0, 0}};

  InitWindow(600, 600, "falling sand");
  SetTargetFPS(60);

  while (WindowShouldClose() == false) {
    BeginDrawing();
    ClearBackground(BLACK);

    if (IsKeyDown(KEY_SPACE)) {
      for (int row = rows - 1; row >= 0; row--) {
        for (int col = 0; col < cols; col++) {
          if (tilemap[row][col] == SAND) {
            if (!IsBlockBelow(tilemap, rows, cols, row, col) &&
                tilemap[row + 1][col] == EMPTY) {
              tilemap[row + 1][col] = SAND;
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
