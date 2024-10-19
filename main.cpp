#include "raylib.h"
#include <ctime>
#include <iostream>
#include <unistd.h>

enum TileType { EMPTY = 0, BLOCK = 1, BEDROCK = 2, SAND = 3 };
int currentType; 

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
      {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, //
      {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, //
      {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, //
      {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, //
      {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, //
      {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, //
      {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, //
      {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, //
      {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, //
      {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, //
      {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, //
      {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, //
      {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, //
      {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, //
      {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, //
      {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, //
      {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, //
      {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}, //
  };

  InitWindow(576, 576, "falling sand");
  SetTargetFPS(60);

  while (WindowShouldClose() == false) {
    BeginDrawing();
    ClearBackground(BLACK);

    int mouseY = GetMouseX() / tileWidth;
    int mouseX = GetMouseY() / tileHeight;

    if (mouseY >= 0 && mouseY < cols && mouseX >= 0 && mouseX < rows) {
      DrawRectangle(mouseY * tileWidth, mouseX * tileHeight, tileWidth, tileHeight, Color{255, 255, 255, 128});
    }

    if (IsKeyPressed(KEY_ONE)){
        currentType = 1;
    }
    if (IsKeyPressed(KEY_TWO)) {
        currentType = 3;
    }

    if (tilemap[mouseX][mouseY] != BEDROCK) {
      if (IsMouseButtonDown(0)) {
        tilemap[mouseX][mouseY] = currentType;
      }

      if (IsMouseButtonDown(1)) {
        tilemap[mouseX][mouseY] = EMPTY;
      }
    }

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
