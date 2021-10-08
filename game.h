#include <string>
#include <vector>

#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"
#include "opponent.h"
#include "player.h"

#ifndef GAME_H
#define GAME_H

class Game : public graphics::AnimationEventListener,
             public graphics::MouseEventListener {
 private:
  graphics::Image GameScreen_;
  std::vector<std::unique_ptr<Opponent>> Opponent_;
  std::vector<std::unique_ptr<OpponentProjectile>> OpponentProjectile_;
  std::vector<std::unique_ptr<PlayerProjectile>> PlayerProjectile_;
  Player Player_;
  int width_;
  int height_;
  int gamescore_ = 0;
  int lost_ = false;

 public:
  Game(int width, int height) { GameScreen_.Initialize(width, height); }
  Game() { GameScreen_.Initialize(800, 600); }

  graphics::Image &GetGameScreen() { return GameScreen_; }
  std::vector<std::unique_ptr<Opponent>> &GetOpponents() { return Opponent_; }
  std::vector<std::unique_ptr<OpponentProjectile>> &GetOpponentProjectiles() {
    return OpponentProjectile_;
  }
  std::vector<std::unique_ptr<PlayerProjectile>> &GetPlayerProjectiles() {
    return PlayerProjectile_;
  }
  Player &GetPlayer() { return Player_; }

  int GetScore() { return gamescore_; }

  bool HasLost() { return lost_; }

  void CreateOpponents();
  void CreateOpponentProjectiles();
  void CreatePlayerProjectiles();
  void Init();
  void Start(graphics::Image &GameBoard);
  void UpdateScreen();
  void MoveGameElements();
  void FilterIntersections();
  void OnAnimationStep();
  void OnMouseEvent(const graphics::MouseEvent &mouse);
  void LaunchProjectiles();
  void RemoveInactive();
};

#endif
