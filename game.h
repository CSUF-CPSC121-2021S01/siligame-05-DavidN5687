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
  std::vector<Opponent> Opponent_;
  std::vector<OpponentProjectile> OpponentProjectile_;
  std::vector<PlayerProjectile> PlayerProjectile_;
  Player Player_;
  int width_;
  int height_;

 public:
  Game(int width, int height) { GameScreen_.Initialize(width, height); }
  Game() { GameScreen_.Initialize(800, 600); }

  graphics::Image &GetGameScreen() { return GameScreen_; }
  std::vector<Opponent> &GetOpponents() { return Opponent_; }
  std::vector<OpponentProjectile> &GetOpponentProjectiles() {
    return OpponentProjectile_;
  }
  std::vector<PlayerProjectile> &GetPlayerProjectiles() {
    return PlayerProjectile_;
  }
  Player &GetPlayer() { return Player_; }

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
};

#endif
