#include "player.h"

#include "cpputils/graphics/image.h"
#include "opponent.h"

// Draw Function
void Player::Draw(graphics::Image &image) {
  graphics::Image imageP;
  imageP.Load("Player.bmp");
  for (int z = 0; z < width_; z++) {
    for (int i = 0; i < height_; i++) {
      image.SetColor(i + x_, z + y_, imageP.GetColor(i, z));
    }
  }
}

void PlayerProjectile::Draw(graphics::Image &image) {
  graphics::Image imagePP;
  imagePP.Load("Pprojectile.bmp");
  for (int z = 0; z < width_; z++) {
    for (int i = 0; i < height_; i++) {
      image.SetColor(i + x_, z + y_, imagePP.GetColor(i, z));
    }
  }
}
void PlayerProjectile::Move(const graphics::Image &image) {
  y_ = y_ - 3;
  if (IsOutOfBounds(image)) {
    SetIsActive(false);
  }
}
