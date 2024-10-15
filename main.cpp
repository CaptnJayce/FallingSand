#include "raylib.h"
#include <iostream>

int arr[5][5] {
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0}
};

int main() {
  const int screenWidth = 1200;
  const int screenHeight = 800;

  InitWindow(screenWidth, screenHeight, "Falling Sand");

  while(WindowShouldClose() == false){
    std::cout << "do some shit" << std::endl;
  }

  CloseWindow();
}

