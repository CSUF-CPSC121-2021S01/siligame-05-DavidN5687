#include "game_element.h"
#include "opponent.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player : public GameElement {
 public:
  // Constructor

  Player(int x, int y) : GameElement(x, y, 50, 50) {}
  Player() {}

  // functions

  void Draw(graphics::Image &image) override;
  void Move(const graphics::Image &image) override {}
};

class PlayerProjectile : public GameElement {
 public:
  // Constructor

  PlayerProjectile(int x, int y) : GameElement(x, y, 5, 5) {}
  PlayerProjectile() {}

  // functions

  void Draw(graphics::Image &image) override;
  void Move(const graphics::Image &image) override;
};

#endif
