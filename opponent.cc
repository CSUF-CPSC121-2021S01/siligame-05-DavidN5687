#include "opponent.h"

#include <iostream>
#include <string>

#include "cpputils/graphics/image.h"

// Draw Function

void Opponent::Draw(graphics::Image &image) {
  graphics::Image imageO;
  imageO.Load("Opponent.bmp");
  for (int z = 0; z < width_; z++) {
    for (int i = 0; i < height_; i++) {
      image.SetColor(i + x_, z + y_, imageO.GetColor(i, z));
    }
  }
}

// Draw Projectile

void OpponentProjectile::Draw(graphics::Image &image) {
  graphics::Image imageOP;
  imageOP.Load("Oprojectile.bmp");
  for (int z = 0; z < width_; z++) {
    for (int i = 0; i < height_; i++) {
      image.SetColor(i + x_, z + y_, imageOP.GetColor(i, z));
    }
  }
}

void Opponent::Move(const graphics::Image &image) {
  SetY(GetY() + 1);
  SetX(GetX() + 1);
  if (IsOutOfBounds(image)) {
    Opponent::SetIsActive(false);
  }
}

void OpponentProjectile::Move(const graphics::Image &image) {
  SetY(GetY() + 3);
  if (IsOutOfBounds(image)) {
    OpponentProjectile::SetIsActive(false);
  }
}
