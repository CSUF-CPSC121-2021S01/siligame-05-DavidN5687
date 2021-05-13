#include "game.h"

int main() {
  Game GameBoard;
  GameBoard.Init();
  GameBoard.Start(GameBoard.GetGameScreen());
}
