#include "game_element.h"

bool GameElement::IntersectsWith(GameElement *universal) {
  return !(GetX() > universal->GetX() + universal->GetWidth() ||
           universal->GetX() > GetX() + GetWidth() ||
           GetY() > universal->GetY() + universal->GetHeight() ||
           universal->GetY() > GetY() + GetHeight());
}
bool GameElement::IsOutOfBounds(const graphics::Image &image) {
  if (x_ + width_ > image.GetWidth() || y_ + height_ > image.GetHeight() ||
      y_ < 0 || x_ < 0) {
    return true;
  } else {
    return false;
  }
}
