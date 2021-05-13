#include "game.h"

#include <iostream>
#include <vector>

#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"

void Game::CreateOpponents() {
  Opponent opponent(100, 25);
  Opponent opponent1(150, 25);
  Opponent opponent2(200, 25);
  Opponent opponent3(250, 25);
  Opponent opponent4(300, 25);
  Opponent opponent5(350, 25);
  Opponent_.push_back(opponent);
  Opponent_.push_back(opponent2);
  Opponent_.push_back(opponent3);
  Opponent_.push_back(opponent4);
  Opponent_.push_back(opponent5);
}

void Game::CreateOpponentProjectiles() {
  OpponentProjectile OpponentProjectile(100, 50);
  OpponentProjectile_.push_back(OpponentProjectile);
}

void Game::CreatePlayerProjectiles() {
  PlayerProjectile PlayerProjectile(125, 50);
  PlayerProjectile_.push_back(PlayerProjectile);
}

void Game::Init() {
  Player_.SetX(200);
  Player_.SetY(125);
  CreateOpponents();
  CreateOpponentProjectiles();
  CreatePlayerProjectiles();
  GameScreen_.AddMouseEventListener(*this);
  GameScreen_.AddAnimationEventListener(*this);
}
void Game::UpdateScreen() {
  GameScreen_.DrawRectangle(0, 0, 800, 600, 255, 255, 255);

  if (Player_.GetIsActive()) {
    Player_.Draw(GameScreen_);
  }

  for (int i = 0; i < Opponent_.size(); i++) {
    if (Opponent_[i].GetIsActive()) {
      Opponent_[i].Draw(GameScreen_);
    }
  }
  for (int i = 0; i < OpponentProjectile_.size(); i++) {
    if (OpponentProjectile_[i].GetIsActive()) {
      OpponentProjectile_[i].Draw(GameScreen_);
    }
  }
  for (int i = 0; i < PlayerProjectile_.size(); i++) {
    if (PlayerProjectile_[i].GetIsActive()) {
      PlayerProjectile_[i].Draw(GameScreen_);
    }
  }
}

void Game::MoveGameElements() {
  for (int i = 0; i < Opponent_.size(); i++) {
    Opponent_[i].Move(GameScreen_);
  }
  for (int x = 0; x < OpponentProjectile_.size(); x++) {
    OpponentProjectile_[x].Move(GameScreen_);
  }
  for (int y = 0; y < PlayerProjectile_.size(); y++) {
    PlayerProjectile_[y].Move(GameScreen_);
  }
}

void Game::Start(graphics::Image &GameBoard) { GameBoard.ShowUntilClosed(); }

void Game::FilterIntersections() {
  // Player and Opponent

  for (int y = 0; y < Opponent_.size(); y++) {
    if (Player_.IntersectsWith(Opponent_[y])) {
      Player_.SetIsActive(false);
      Opponent_[y].SetIsActive(false);
    }
  }

  // PlayerProjectile and Opponent

  for (int i = 0; i < PlayerProjectile_.size(); i++) {
    for (int o = 0; o < Opponent_.size(); o++) {
      if (PlayerProjectile_[i].IntersectsWith(Opponent_[o])) {
        PlayerProjectile_[i].SetIsActive(false);
        Opponent_[o].SetIsActive(false);
      }
    }
  }

  // OpponentProjectile and Player

  for (int l = 0; l < OpponentProjectile_.size(); l++) {
    if (OpponentProjectile_[l].IntersectsWith(Player_)) {
      OpponentProjectile_[l].SetIsActive(false);
      Player_.SetIsActive(false);
    }
  }
}

void Game::OnAnimationStep() {
  MoveGameElements();
  FilterIntersections();
  UpdateScreen();
  GameScreen_.Flush();
}

void Game::OnMouseEvent(const graphics::MouseEvent &mouse) {
  if (mouse.GetX() < GameScreen_.GetWidth() &&
      mouse.GetY() < GameScreen_.GetHeight() && mouse.GetX() > 0 &&
      mouse.GetY() > 0) {
    Player_.SetX(mouse.GetX() - Player_.GetWidth() / 2);
    Player_.SetY(mouse.GetY() - Player_.GetHeight() / 2);
  }
}
