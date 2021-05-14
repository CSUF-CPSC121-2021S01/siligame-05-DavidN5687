#include "cpputils/graphics/image.h"

#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H

class GameElement {
 protected:
  int x_;
  int y_;
  int width_;
  int height_;
  bool is_active = true;

 public:
  // Constructor
  GameElement() {
    x_ = 0;
    y_ = 0;
    width_ = 50;
    height_ = 50;
  }
  GameElement(int x, int y, int width, int height)
      : x_(x), y_(y), width_(width), height_(height) {}

  // setters and getters

  int GetX() const { return x_; }
  void SetX(int x) { x_ = x; }

  int GetY() const { return y_; }
  void SetY(int y) { y_ = y; }

  int GetWidth() const { return width_; }
  int GetHeight() const { return height_; }

  bool GetIsActive() { return is_active; }
  void SetIsActive(bool is_active_) { is_active = is_active_; }

  // functions

  bool IntersectsWith(GameElement *universal);

  bool IsOutOfBounds(const graphics::Image &universal);

  // virtual functions

  virtual void Draw(graphics::Image &BRect) = 0;

  virtual void Move(const graphics::Image &image) = 0;
};

#endif
