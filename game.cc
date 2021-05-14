#include "game.h"

#include <iostream>
#include <vector>

#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"

void Game::CreateOpponents() {
  for (int i = 0; i < 3; i++) {
    Opponent_.push_back(std::make_unique<Opponent>(50 * i + 15, 50));
  }
}

void Game::Init() {
  Player_.SetX(200);
  Player_.SetY(125);
  GameScreen_.AddMouseEventListener(*this);
  GameScreen_.AddAnimationEventListener(*this);
}
void Game::UpdateScreen() {
  GameScreen_.DrawRectangle(0, 0, 800, 600, 255, 255, 255);

  if (Player_.GetIsActive()) {
    Player_.Draw(GameScreen_);
  } else {
    GameScreen_.DrawText(300, 300, "Game Over", 35, 0, 0, 0);
  }

  for (int i = 0; i < Opponent_.size(); i++) {
    if (Opponent_[i]->GetIsActive()) {
      Opponent_[i]->Draw(GameScreen_);
    }
  }
  for (int i = 0; i < OpponentProjectile_.size(); i++) {
    if (OpponentProjectile_[i]->GetIsActive()) {
      OpponentProjectile_[i]->Draw(GameScreen_);
    }
  }
  for (int i = 0; i < PlayerProjectile_.size(); i++) {
    if (PlayerProjectile_[i]->GetIsActive()) {
      PlayerProjectile_[i]->Draw(GameScreen_);
    }
  }
  GameScreen_.DrawText(10, 10, std::to_string(gamescore_), 35, 0, 0, 0);
}

void Game::MoveGameElements() {
  for (int i = 0; i < Opponent_.size(); i++) {
    Opponent_[i]->Move(GameScreen_);
  }
  for (int x = 0; x < OpponentProjectile_.size(); x++) {
    OpponentProjectile_[x]->Move(GameScreen_);
  }
  for (int y = 0; y < PlayerProjectile_.size(); y++) {
    PlayerProjectile_[y]->Move(GameScreen_);
  }
}

void Game::Start(graphics::Image &GameBoard) { GameBoard.ShowUntilClosed(); }

void Game::FilterIntersections() {
  // Player and Opponent

  for (int y = 0; y < Opponent_.size(); y++) {
    if (Player_.IntersectsWith(Opponent_[y].get()) == true) {
      Player_.SetIsActive(false);
      Opponent_[y]->SetIsActive(false);
      lost_ = true;
    }
  }

  // PlayerProjectile and Opponent

  for (int i = 0; i < PlayerProjectile_.size(); i++) {
    for (int o = 0; o < Opponent_.size(); o++) {
      if (PlayerProjectile_[i]->IntersectsWith(Opponent_[o].get()) == true) {
        PlayerProjectile_[i]->SetIsActive(false);
        Opponent_[o]->SetIsActive(false);
        if (Player_.GetIsActive() == true) {
          gamescore_++;
        }
      }
    }
  }

  // OpponentProjectile and Player

  for (int l = 0; l < OpponentProjectile_.size(); l++) {
    if (OpponentProjectile_[l]->IntersectsWith(&Player_) == true) {
      OpponentProjectile_[l]->SetIsActive(false);
      Player_.SetIsActive(false);
      lost_ = true;
    }
  }
}

void Game::OnAnimationStep() {
  if (Opponent_.size() == 0) {
    CreateOpponents();
  }
  MoveGameElements();
  LaunchProjectiles();
  FilterIntersections();
  RemoveInactive();
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
  if (mouse.GetMouseAction() == graphics::MouseAction::kPressed) {
    std::unique_ptr<PlayerProjectile> star =
        std::make_unique<PlayerProjectile>(mouse.GetX(), mouse.GetY() + 25);
    PlayerProjectile_.push_back(std::move(star));
  }
  if (mouse.GetMouseAction() == graphics::MouseAction::kDragged) {
    std::unique_ptr<PlayerProjectile> star =
        std::make_unique<PlayerProjectile>(mouse.GetX(), mouse.GetY() + 25);
    PlayerProjectile_.push_back(std::move(star));
  }
}

void Game::LaunchProjectiles() {
  for (int i = 0; i < Opponent_.size(); i++) {
    if (Opponent_[i]->LaunchProjectile() != nullptr) {
      std::unique_ptr<OpponentProjectile> star;
      star = std::make_unique<OpponentProjectile>();
      star->SetX(Opponent_[i]->GetX());
      star->SetY(Opponent_[i]->GetY());
      OpponentProjectile_.push_back(std::move(star));
    }
  }
}

void Game::RemoveInactive() {
  for (int i = PlayerProjectile_.size() - 1; i >= 0; i--) {
    if (PlayerProjectile_[i]->GetIsActive() == false) {
      PlayerProjectile_.erase(PlayerProjectile_.begin() + i);
    }
  }
  for (int i = OpponentProjectile_.size() - 1; i >= 0; i--) {
    if (OpponentProjectile_[i]->GetIsActive() == false) {
      OpponentProjectile_.erase(OpponentProjectile_.begin() + i);
    }
  }
  for (int i = Opponent_.size() - 1; i >= 0; i--) {
    if (!Opponent_[i]->GetIsActive()) {
      Opponent_.erase(Opponent_.begin() + i);
    }
  }
}
