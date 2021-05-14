#include "cpputils/graphics/image.h"
#include "game_element.h"

#ifndef OPPONENT_H
#define OPPONENT_H

class Opponent : public GameElement {
 private:
  int FireRate_ = 0;

 public:
  Opponent(int x, int y) : GameElement(x, y, 50, 50) {}
  Opponent() {}
  void Draw(graphics::Image &image) override;
  void Move(const graphics::Image &image) override;
  std::unique_ptr<class OpponentProjectile> LaunchProjectile();
};

class OpponentProjectile : public GameElement {
 public:
  OpponentProjectile(int x, int y) : GameElement(x, y, 5, 5) {}
  OpponentProjectile() {}
  void Draw(graphics::Image &image) override;
  void Move(const graphics::Image &image) override;
};

#endif
